#pragma once
#include "Controladora.h"

namespace ConsoleApplication3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		//Componentes de graficador
		BufferedGraphicsContext^space;
		BufferedGraphics^ buffer;

		Controladora* objControlador = new Controladora();

		Bitmap^ bmpBloque = gcnew Bitmap("Imagenes\\bloque.png");
		Bitmap^ bmpBase = gcnew Bitmap("Imagenes\\base_1.png");
		Bitmap^ bmpfuego = gcnew Bitmap("Imagenes\\bolafuego.png");
		Bitmap^ Enemigos = gcnew Bitmap("Imagenes\\Banette.png");
	private: System::Windows::Forms::Timer^  timer1;
			 Bitmap^ bmpJugador = gcnew Bitmap("Imagenes\\Picachu.png");
			 //Bitmap ^ Enemigo = gcnew Bitmap("Imagenes\\canon.png");
			// Bitmap ^ bala = gcnew Bitmap("Imagenes\\fuego.png");
			 Bitmap ^ Compuerta = gcnew Bitmap("Imagenes\\portal.jpg");

	public:
		MyForm(void)
		{
			InitializeComponent();

			this->space = BufferedGraphicsManager::Current;
			this->buffer = space->Allocate(this->CreateGraphics(), this->ClientRectangle);


			bmpJugador->MakeTransparent(Color::White);
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se est�n usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Variable del dise�ador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// M�todo necesario para admitir el Dise�ador. No se puede modificar
		/// el contenido de este m�todo con el editor de c�digo.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 80;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(902, 596);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion

		void Iniciar_Juego() {
			this->Text = L"VIDAS : " + objControlador->Vidas().ToString();
			objControlador->DibujarMapa(buffer->Graphics, bmpBloque, bmpfuego, bmpBase);
			objControlador->DibujarJugador(buffer->Graphics, bmpJugador);
			//objControlador->DibujaEnemigos(buffer->Graphics , Enemigo , bala );
			objControlador->DibujaCompuerta(buffer->Graphics, Compuerta);
			objControlador->ColisionEnemigoJugador();
			objControlador->DibujaEnemigos(buffer->Graphics,Enemigos,bmpfuego);
			//objControlador->InteraccionJyEsc();
			objControlador->PierdeJuego();
			objControlador->GanaJuego();
		}

	 private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

		Iniciar_Juego();
		buffer->Render();

	}



	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

		switch (e->KeyCode)
		{

		case Keys::Left: {objControlador->DireccionJugador(Direcciones::izquierda); }break;
		case Keys::Right: {objControlador->DireccionJugador(Direcciones::derecha); }break;
		case Keys::Up: {objControlador->DireccionJugador(Direcciones::arriba); }break;
		case Keys::Down: {objControlador->DireccionJugador(Direcciones::abajo); }break;

		}
	}



	private: System::Void MyForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		objControlador->DireccionJugador(Direcciones::ninguna);
	}

private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
