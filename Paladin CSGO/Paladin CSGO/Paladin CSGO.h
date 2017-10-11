#pragma once
#pragma once
#include <tchar.h>
#include "Windows.h"
#include <tlhelp32.h>
#include <iostream>
#include <atomic>
#include <chrono>
#include <ctime>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
namespace PaladinCSGO {
	public ref class PaladinCSGO : public System::Windows::Forms::Form
	{
	public:
		PaladinCSGO(void)
		{
			InitializeComponent();
		}

	protected:
		~PaladinCSGO()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300,300);
			this->Text = L"PaladinCSGO";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
