/* =============================================================
   Curso      : Estructura de Datos (24UC00428)
   Evaluacion : C2 - Medicion de competencias - Semana 12
   Proyecto   : Tux Store v2 (kit base)
   Institucion: Universidad Continental
   Semestre   : 2026-20
   Compilador : Dev-C++ (MinGW / GCC, C++11 o superior)
   NRC        :42964
   Grupo      : "G"
   Integrantes: Danny Abel león Huamán
                Juan Dennys Cayllahua Apaza 
                Eduardo Alexander Quinta Justo
                Juan Carlos Chani Chullo
                Cristofer Tonny Yanqui Laura
                Eduardo Alexander Quinta Justo
   ============================================================= */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

const int DISPONIBLE = 0;
const int EN_FILA    = 1;
const int INSTALADA  = 2;
const string ARCHIVO = "tuxstore.txt";

struct NodoApp {
    string nombre;
    string version;
    int    mb;
    int    prioridad;
    int    estado;
    int    inicio, fin, espera;
    NodoApp *sig;
};

struct NodoFila {
    string nombre;
    int    llegada;
    int    prioridad;
    NodoFila *sig;
};

struct NodoBloque {
    string nombre;
    int    mb;
    NodoBloque *sig;
};

// ===== FICHA ===== 
const string SERVIDOR = "pinguino-magallanes";
const int VELOCIDAD = 3;
const int DISCO = 274;
const int N_APPS = 8;
string fNombre[N_APPS] = {"fail2ban", "nginx", "python3", "firefox", "libreoffice", "krita", "cmatrix", "steam"};
string fVersion[N_APPS] = {"1.0", "1.24", "3.12", "128", "24.2", "5.2", "2.0", "1.0"};
int fMb[N_APPS] = {2, 12, 38, 210, 380, 180, 1, 9};
int fPrio[N_APPS] = {1, 1, 2, 2, 2, 3, 3, 3};
// =================

string estadoTexto(int e) {
    if (e == DISPONIBLE) return "disponible";
    if (e == EN_FILA)    return "en fila";
    return "instalada";
}

NodoApp* crearApp(string nombre, string version, int mb, int prioridad) {
    NodoApp *n = new NodoApp;
    n->nombre = nombre; n->version = version; n->mb = mb; n->prioridad = prioridad;
    n->estado = DISPONIBLE;
    n->inicio = n->fin = n->espera = -1;
    n->sig = nullptr;
    return n;
}

void mostrarApp(NodoApp *a) {
    cout << "  " << left << setw(12) << a->nombre << setw(9) << a->version
         << right << setw(5) << a->mb << " MB   prioridad " << a->prioridad
         << "   " << estadoTexto(a->estado) << endl;
}

bool aEntero(string s, int &v) {
    if (s == "") return false;
    int i = 0, signo = 1; v = 0;
    if (s[0] == '-') { signo = -1; i = 1; if (s.size() == 1) return false; }
    for (; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
        v = v * 10 + (s[i] - '0');
    }
    v *= signo;
    return true;
}

NodoApp* buscarApp(NodoApp *catalogo, string nombre) {
    // TODO R1a
     for (NodoApp *p = catalogo; p != nullptr; p = p->sig) {
        if (p->nombre == nombre) return p;
    }
    return nullptr;
}

bool agregarAlFinal(NodoApp *&catalogo, string nombre, string version, int mb, int prioridad) {
    // TODO R1b
   if (buscarApp(catalogo, nombre) != nullptr) return false;

    NodoApp *n = crearApp(nombre, version, mb, prioridad);
    if (catalogo == nullptr) {
        catalogo = n;
        return true;
    }

    NodoApp *p = catalogo;
    while (p->sig != nullptr) p = p->sig;
    p->sig = n;
    return true;
}

void encolarConPrioridad(NodoFila *&frente, NodoFila *&final, string nombre, int llegada, int prioridad) {
    // TODO R2a
   NodoFila *n = new NodoFila;
    n->nombre = nombre;
    n->llegada = llegada;
    n->prioridad = prioridad;
    n->sig = nullptr;

    if (frente == nullptr) {
        frente = final = n;
        return;
    }

    if (prioridad < frente->prioridad || (prioridad == frente->prioridad && llegada < frente->llegada)) {
        n->sig = frente;
        frente = n;
        if (final == nullptr) final = n;
        return;
    }

    NodoFila *p = frente;
    while (p->sig != nullptr &&
           (p->sig->prioridad < prioridad ||
            (p->sig->prioridad == prioridad && p->sig->llegada < llegada))) {
        p = p->sig;
    }

    n->sig = p->sig;
    p->sig = n;
    if (p == final) final = n;
}

void leerOrden(string linea, string &orden, string &a1, string &a2, string &a3, string &a4) {
    string t[8]; int n = 0;
    stringstream ss(linea);
    while (n < 8 && ss >> t[n]) n++;
    orden = a1 = a2 = a3 = a4 = "";
    if (n == 0) return;
    int k = 0;
    if (t[0] == "sudo") k = 1;
    string c = (k < n) ? t[k] : "";
    if (c == "apt" && k + 1 < n) {
        string s = t[k + 1];
        if (s == "list") orden = "catalogo";
        else if (s == "search") orden = "buscar";
        else if (s == "show") orden = "info";
        else if (s == "install") orden = "instalar";
        else if (s == "purge") orden = "retirar";
        else orden = "apt " + s;
        k += 2;
    } else if (c == "dnf" && k + 2 < n && t[k + 1] == "history" && t[k + 2] == "undo") {
        orden = "deshacer"; k = n;
    } else if (c == "dnf" && k + 1 < n && t[k + 1] == "history") {
        orden = "historial"; k = n;
    } else if (c == "dpkg" && k + 1 < n && t[k + 1] == "--get-selections") { orden = "guardar"; k = n; }
    else if (c == "dpkg" && k + 1 < n && t[k + 1] == "--set-selections") { orden = "cargar"; k = n; }
    else if (c == "df")   { orden = "espacio"; k = n; }
    else if (c == "man" || c == "help" || c == "--help") { orden = "ayuda"; k = n; }
    else if (c == "exit") { orden = "salir"; k = n; }
    else { orden = c; k++; }
    if (k < n) a1 = t[k];
    if (k + 1 < n) a2 = t[k + 1];
    if (k + 2 < n) a3 = t[k + 2];
    if (k + 3 < n) a4 = t[k + 3];
}

void ayuda() {
    cout << "  ORDEN (espanol)            EN LINUX                      QUE HACE" << endl;
    cout << "  catalogo                   apt list                      ver todas las apps" << endl;
    cout << "  buscar <texto>             apt search <texto>            buscar por nombre" << endl;
    cout << "  info <app>                 apt show <app>                ficha de una app" << endl;
    cout << "  agregar <app> <v> <MB> <p> -                             nueva app (p = 1, 2 o 3)" << endl;
    cout << "  prioridad <app> <p>        -                             cambiar la prioridad" << endl;
    cout << "  retirar <app>              sudo apt purge <app>          borrar del catalogo" << endl;
    cout << "  instalar <app> <seg>       sudo apt install <app> <seg>  pedir una app" << endl;
    cout << "  fila                       -                             ver la fila de descargas" << endl;
    cout << "  procesar                   -                             descargar la del frente" << endl;
    cout << "  historial                  dnf history                   bloques de disco (pila)" << endl;
    cout << "  deshacer                   dnf history undo last         liberar el ultimo bloque" << endl;
    cout << "  espacio                    df                            estado del disco" << endl;
    cout << "  guardar                    dpkg --get-selections         guardar en tuxstore.txt" << endl;
    cout << "  cargar                     dpkg --set-selections         cargar tuxstore.txt" << endl;
    cout << "  reporte                    -                             resumen del turno" << endl;
    cout << "  salir                      exit                          terminar" << endl;
}

int main() {
    NodoApp    *catalogo = nullptr;
    NodoFila   *frente = nullptr, *final = nullptr;
    NodoBloque *tope = nullptr;

    int reloj = 0, libre = DISCO, ultimaLlegada = 0;
    int instalaciones = 0, sumaEspera = 0, mbDescargados = 0;

    for (int i = 0; i < N_APPS; i++) agregarAlFinal(catalogo, fNombre[i], fVersion[i], fMb[i], fPrio[i]);

    cout << "Tux Store - servidor " << SERVIDOR << " (" << VELOCIDAD << " MB/s, "
         << DISCO << " MB). Escribe ayuda." << endl;

    string linea;
    while (true) {
        cout << "tux@" << SERVIDOR << ":~$ ";
        if (!getline(cin, linea)) break;
        string orden, a1, a2, a3, a4;
        leerOrden(linea, orden, a1, a2, a3, a4);
        if (orden == "") continue;
        cout << "> " << linea << endl;

        if (orden == "catalogo") {
            // TODO R1c
              if (catalogo == nullptr) cout << "Catalogo vacio" << endl;
            else {
                for (NodoApp *p = catalogo; p != nullptr; p = p->sig) {
                    mostrarApp(p);
                }
            }
        }
        else if (orden == "buscar") {
            // TODO R1d
            if (a1 == "") cout << "E: Debes indicar un texto" << endl;
            else {
                bool hay = false;
                for (NodoApp *p = catalogo; p != nullptr; p = p->sig) {
                    if (p->nombre.find(a1) != string::npos || p->version.find(a1) != string::npos) {
                        mostrarApp(p);
                        hay = true;
                    }
                }
                if (!hay) cout << "E: No se encontro " << a1 << endl;
            }
        }
        else if (orden == "info") {
            // TODO R1e
              NodoApp *a = buscarApp(catalogo, a1);
            if (a == nullptr) cout << "E: No se encontro " << a1 << endl;
            else {
                cout << "  " << left << setw(12) << a->nombre << setw(9) << a->version
                     << right << setw(5) << a->mb << " MB   prioridad " << a->prioridad
                     << "   " << estadoTexto(a->estado) << endl;
            }
        }
        
        else if (orden == "agregar") {
            // TODO R1f
              if (a1 == "" || a2 == "" || a3 == "" || a4 == "") {
                cout << "E: Uso: agregar <app> <version> <MB> <prioridad>" << endl;
            } else {
                int mb, prio;
                if (!aEntero(a3, mb) || !aEntero(a4, prio) || mb <= 0 || prio < 1 || prio > 3) {
                    cout << "E: Datos invalidos para agregar " << a1 << endl;
                } else if (!agregarAlFinal(catalogo, a1, a2, mb, prio)) {
                    cout << "E: No se pudo agregar " << a1 << endl;
                } else {
                    cout << "Agregada: " << a1 << " " << a2 << endl;
                }
            }
        }
        else if (orden == "instalar") {
            // TODO R2b
            int seg;
            // Validar que el usuario ingreso a la app y el tiempo
            if (a1 == "" || a2 == "") {
               cout << "E: Uso: instalar <app> <segundos>" << endl;
            // Validar que el timepo ingresado sea positivo
            } else if (!aEntero(a2, seg) || seg < 0) {
               cout << "E: El valor de tiempo debe ser positivo" << endl;
            } else {
            // Buscar si la aplicacion existe en el catalogo
               NodoApp *app = buscarApp(catalogo, a1);
                  if (app == nullptr) {
                     cout << "E: La app no existe" << a1 << endl;
            // Verificar que la app no haya sido pedida
                  } else if (app->estado != DISPONIBLE) {
                     cout << "E: La app " << a1 << " ya esta en la fila o instalada" << endl;
            // Regla del servidor (el tiempo ingresado no puede retroceder)
                  } else if (seg < ultimaLlegada) {
                     cout << "E: El segundo " << seg << " retrocede el tiempo (ultimo pedido: " << ultimaLlegada << ")" << endl;
                  } else {
            // Si pasa todos los filtros, ingresa a la cola y actualiza variables
                  encolarConPrioridad(frente, final, app->nombre, seg, app->prioridad);
                     app->estado = EN_FILA;
                     ultimaLlegada = seg;
                     cout << "En fila: " << app->nombre << " (prioridad " << app->prioridad << ")" << endl;
                  }
            }
        }
        else if (orden == "fila") {
            // TODO R2c
           if (frente == nullptr) {
              cout << "(fila vacia)" << endl;
           } else {
            // Recorrer la cola desde el frente hasta el final
              cout << " frente";
              NodoFila *p = frente;
              while (p != nullptr) {
                 cout << " -> " << p->nombre << "(" << p->prioridad << ")";
                 p = p->sig;
              }
              cout << " <- final" << endl;
           }
        }
        else if (orden == "procesar") {
            // TODO R3
            if (frente == nullptr){
            // Validar si la fila de descargas esta vacia
               cout << "La fila esta vacia" << endl;
            } else {
            // Extraer el nodo de la fila
               NodoFila *pedido = frente;
               frente = frente->sig;
               if (frente == nullptr) final = nullptr;

               NodoApp *app = buscarApp(catalogo, pedido->nombre);

               if (app->mb > libre) {
               // Verificar espacio (si no hay suficiente, se cancela y vuelve a estar disponible)
                  cout << "E: No hay espacio suficiente para " << app->nombre
                        << ": necesita" << app->mb << " Mb, libres " << libre << " MB" << endl;
                  app->estado = DISPONIBLE;
               } else {
               // Calcular los tiempos de descarga
                  int descarga = (app->mb + VELOCIDAD -1) / VELOCIDAD;
                  if (reloj > pedido->llegada)
                     app->inicio = reloj;
                  else
                     app->inicio = pedido->llegada;

                  app->fin = app->inicio + descarga;
                  app->espera = app->inicio - pedido->llegada;
                  reloj = app->fin;
                  libre = libre - app->mb;

                  // Actualizar estadisticas y marcar como instalada
                  instalaciones++;
                  mbDescargados = mbDescargados + app->mb;
                  sumaEspera = sumaEspera + app->espera;
                  app->estado = INSTALADA;

                  // Apilar el bloque en el historial para ser usado por el modulo de disco
                  NodoBloque *bloque = new NodoBloque;
                  bloque->nombre = app->nombre;
                  bloque->mb = app->mb;
                  bloque->sig = tope;
                  tope = bloque;

                  cout << app->nombre << ": descarga " << descarga << " s | inicio " << app->inicio
                        << " | fin " << app->fin<< " | espera " << app->espera
                        << " | libres " << libre << " MB" << endl;
               }
               delete pedido;
            } 
        }
        else if (orden == "historial") {
           // TODO R4a
           if (tope == nullptr) {
               cout << "Historial vacío" << endl;
           } else {
               cout << "Historial del disco (tope → fondo):" << endl;
               NodoBloque *actual = tope;
               while (actual != nullptr) {
               cout << "  " << actual->nombre << " - " << actual->mb << " MB" << endl;
               actual = actual->sig;
               }
           }
        }
        else if (orden == "deshacer") {
           // TODO R4b
           if (tope == nullptr) {
               cout << "E: No hay nada que deshacer" << endl;
           } 
           else {
               NodoBloque *bloque = tope;
               tope = tope->sig;
               libre += bloque->mb;
              
        // Poner la app como disponible
        NodoApp *app = buscarApp(catalogo, bloque->nombre);
             if (app != nullptr) {
                 app->estado = DISPONIBLE;
                 app->inicio = app->fin = app->espera = -1;
             }
           cout << "Deshecho: " << bloque->nombre << " (" << bloque->mb << " MB liberados)" << endl;
           delete bloque;
           }
        }
        else if (orden == "espacio") {
           // TODO R4c
           int ocupado = DISCO - libre;
           int bloques = 0;
           NodoBloque *actual = tope;
           while (actual != nullptr) {
                  bloques++;
                  actual = actual->sig;
           }
           cout << "Disco: " << DISCO << " MB total" << endl;
           cout << "Ocupado: " << ocupado << " MB" << endl;
           cout << "Libre: " << libre << " MB" << endl;
           cout << "Bloques: " << bloques << endl;
        }
        else if (orden == "prioridad") {
            // TODO R5a
        }
        else if (orden == "retirar") {
            // TODO R5b
        }
        else if (orden == "guardar") {
            if (frente != nullptr) cout << "E: Procesen la fila antes de guardar" << endl;
            else {
                ofstream f(ARCHIVO);
                int n = 0, m = 0;
                // TODO R6a
                f.close();
                cout << "Guardado: " << n << " apps y " << m << " bloques en " << ARCHIVO << endl;
            }
        }
        else if (orden == "cargar") {
            ifstream f(ARCHIVO);
            if (!f) cout << "E: No existe " << ARCHIVO << endl;
            else if (frente != nullptr) cout << "E: Procesen la fila antes de cargar" << endl;
            else {
                int n = 0, m = 0;
                // TODO R6b
                cout << "Cargado: " << n << " apps y " << m << " bloques | libres " << libre
                     << " MB | turno nuevo" << endl;
            }
        }
        else if (orden == "reporte") {
            // TODO R7a
        }
        else if (orden == "ayuda") ayuda();
        else if (orden == "salir") break;
        else cout << orden << ": orden no encontrada (escribe ayuda)" << endl;
    }

    int liberados = 0;
    // TODO R7b
    cout << "Nodos liberados: " << liberados << ". Hasta pronto." << endl;
    return 0;
}
