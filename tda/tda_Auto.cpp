#include <cstdlib>

class Auto {
	private:
		int id;
		int velAct;
		float cantGas;
		bool motEnc;
		int cambAct;
		string *color;
		
	public:
		Auto() {
			id = rand() % 100; motEnc=false; velAct=0; cantGas=0.0; cambAct=0;
		};
		~Auto(){}
		void arrancar();
		void acelerar();
		void frenar();
		bool tieneGas();
		void cargarGas(float cant);
		void consumirGas();
		void subirCambio();
		void bajarCambio();
		void neutro();
		int getVelAct();
		int getId();
		float getCantGas();
		bool pruebaFuncionamiento();
};

