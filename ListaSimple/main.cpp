#include <iostream>
#include <string>

using namespace std;

template<class T>
class SocioClub;

template<class T>
class Socio {
private:
    T NumeroSocio;
    T AnoIngreso;
    string NombreSocio;
    string Domicilio;
    Socio<T>* sig;
public:
    Socio(): sig(nullptr) {};
    friend class SocioClub<T>;

    friend istream& operator>>(istream& input, Socio<T>& socio) {
        cout << "Numero de socio: ";
        input >> socio.NumeroSocio;
        cout << "Ano de ingreso: ";
        input >> socio.AnoIngreso;
        cout << "Nombre del socio: ";
        input.ignore();
        getline(input, socio.NombreSocio);
        cout << "Domicilio del socio: ";
        getline(input, socio.Domicilio);
        return input;
    }

    friend ostream& operator<<(ostream& output, const Socio<T>& socio) {
        output << "Numero de Socio: " << socio.NumeroSocio << "\nNombre: " << socio.NombreSocio << "\nDomicilio: " << socio.Domicilio << "\nAno de Ingreso: " << socio.AnoIngreso;
        return output;
    }
};

template<class T>
class SocioClub {
private:
    Socio<T>* lista;
    int totalSocios;
public:
    SocioClub(): lista(nullptr), totalSocios(0) {};
    ~SocioClub();
    bool vacia() const;
    Socio<T>* ultimo() const;
    Socio<T>* primero() const;
    Socio<T>* anterior(Socio<T>* pos) const;
    void insertar(const Socio<T>& socio);
    bool eliminar(Socio<T>* pos);
    void imprimir() const;
    Socio<T>* buscarPorNombreODomicilio(string nombreODomicilio) const;
    int calcularTotalSocios() const;
};

template<class T>
SocioClub<T>::~SocioClub() {
    Socio<T>* aux = lista;
    while (aux != nullptr) {
        Socio<T>* temp = aux;
        aux = aux->sig;
        delete temp;
    }
}

template<class T>
void SocioClub<T>::imprimir() const {
    Socio<T>* aux = lista;
    while (aux != nullptr) {
        cout << *aux << "\n\n\n";
        aux = aux->sig;
    }
}

template<class T>
bool SocioClub<T>::eliminar(Socio<T>* pos) {
    if (vacia() || pos == nullptr) {
        return false;
    }
    if (pos == lista) {
        lista = lista->sig;
    } else {
        anterior(pos)->sig = pos->sig;
    }
    delete pos;
    totalSocios--;
    return true;
}

template<class T>
void SocioClub<T>::insertar(const Socio<T>& socio) {
    Socio<T>* existe = lista;
    while (existe != nullptr) {
        if (existe->NumeroSocio == socio.NumeroSocio) {
            cout << "Error: Ya existe un socio con ese numero.\n";
            return;
        }
        existe = existe->sig;
    }
    Socio<T>* aux = new Socio<T>(socio);
    if (vacia() || socio.NumeroSocio < lista->NumeroSocio) {
        aux->sig = lista;
        lista = aux;
    } else {
        Socio<T>* anterior = nullptr;
        Socio<T>* actual = lista;

        while (actual != nullptr && actual->NumeroSocio < socio.NumeroSocio) {
            anterior = actual;
            actual = actual->sig;
        }

        aux->sig = actual;
        if (anterior != nullptr) {
            anterior->sig = aux;
        } else {
            lista = aux;
        }
    }
    totalSocios++;
    cout << "Socio registrado exitosamente.";
}

template<class T>
Socio<T>* SocioClub<T>::anterior(Socio<T>* pos) const {
    if (vacia() || pos == nullptr) {
        return nullptr;
    }
    Socio<T>* aux = lista;
    while (aux != nullptr && aux->sig != pos) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
Socio<T>* SocioClub<T>::primero() const {
    return lista;
}

template<class T>
Socio<T>* SocioClub<T>::ultimo() const {
    if (vacia()) {
        return nullptr;
    }
    Socio<T>* aux = lista;
    while (aux->sig != nullptr) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
bool SocioClub<T>::vacia() const {
    return lista == nullptr;
}

template<class T>
Socio<T>* SocioClub<T>::buscarPorNombreODomicilio(string nombreODomicilio) const {
    Socio<T>* aux = lista;
    while (aux != nullptr) {
        if (aux->NombreSocio == nombreODomicilio || aux->Domicilio == nombreODomicilio) {
            return aux;
        }
        aux = aux->sig;
    }
    return nullptr;
}

template<class T>
int SocioClub<T>::calcularTotalSocios() const {
    return totalSocios;
}

void mostrarMenu() {
    system("cls");
    cout << "SocioClub\nMenu Principal:\n\n";
    cout << "1) Registrar nuevo socio\n";
    cout << "2) Generar reporte de socios\n";
    cout << "3) Buscar socio por nombre o domicilio\n";
    cout << "4) Calcular e imprimir total de socios\n";
    cout << "5) Salir\n";
    cout << "\nOpcion: ";
}

void pausa() {
    cout << "\nPresione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    SocioClub<int> miClub;
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                system("cls");
                Socio<int> nuevoSocio;
                cin >> nuevoSocio;
                miClub.insertar(nuevoSocio);
                pausa();
                break;
            }
            case 2:
                system("cls");
                cout << "\n--- Reporte de Socios ---\n";
                miClub.imprimir();
                pausa();
                break;
            case 3: {
                system("cls");
                string valorBuscado;
                cout << "Ingrese el nombre o domicilio a buscar: ";
                cin.ignore();
                getline(cin, valorBuscado);
                Socio<int>* socioEncontrado = miClub.buscarPorNombreODomicilio(valorBuscado);
                if (socioEncontrado != nullptr) {
                    cout << "\nSocio encontrado - " << *socioEncontrado;
                } else {
                    cout << "\nSocio no encontrado.";
                }
                pausa();
                break;
            }
            case 4:
                system("cls");
                cout << "\nTotal de socios en el club: " << miClub.calcularTotalSocios();
                pausa();
                break;
            case 5:
                system("cls");
                cout << "\nSaliendo del programa. Hasta luego.\n";
                break;
            default:
                cout<<"\nIngrese una opcion valida.";
                pausa();
                break;
        }

    } while (opcion != 5);

    return 0;
}
