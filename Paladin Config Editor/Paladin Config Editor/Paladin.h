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
namespace PaladinConfigEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Paladin
	/// </summary>
	public ref class Paladin : public System::Windows::Forms::Form
	{
	public:
		Paladin(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Paladin()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::TabControl^  Tabs;
    protected:
    private: System::Windows::Forms::TabPage^  keys;
    private: System::Windows::Forms::TabPage^  misc;
    private: System::Windows::Forms::TabPage^  aimrcs;
    private: System::Windows::Forms::TabPage^  trig;
    private: System::Windows::Forms::TabPage^  setting;
    private: System::Windows::Forms::ToolTip^  tooltips;
    private: System::Windows::Forms::Panel^  HitSound_p;

    private: System::Windows::Forms::CheckBox^  enabled_hit;
    private: System::Windows::Forms::Panel^  smooth_p;


    private: System::Windows::Forms::CheckBox^  enabled_smooth;
    private: System::Windows::Forms::Label^  smooth_l;
    private: System::Windows::Forms::Label^  HitSound_L;
    private: System::Windows::Forms::TrackBar^  hitsound_freq_s;

    private: System::Windows::Forms::TrackBar^  hitsound_dur_s;
    private: System::Windows::Forms::Panel^  panel1;
    private: System::Windows::Forms::Label^  keyexit_L;
    private: System::Windows::Forms::Label^  keybind_l;
    private: System::Windows::Forms::TrackBar^  smooth_min_s;
    private: System::Windows::Forms::TrackBar^  smooth_max_s;


    private: System::Windows::Forms::Label^  bhop_L;

    private: System::Windows::Forms::Label^  trig_L;

    private: System::Windows::Forms::Label^  aim_L;

    private: System::Windows::Forms::Label^  reload_L;
    private: System::Windows::Forms::Panel^  slow_p;
    private: System::Windows::Forms::TrackBar^  slowfactor;



    private: System::Windows::Forms::Label^  slowaim_l;
    private: System::Windows::Forms::CheckBox^  slow_enabled;


    private: System::Windows::Forms::Panel^  bunny_p;

    private: System::Windows::Forms::TrackBar^  next_delay_jump;



    private: System::Windows::Forms::TrackBar^  hitchance;
    private: System::Windows::Forms::Label^  bunny_L;


    private: System::Windows::Forms::CheckBox^  enabled_bhop;
    private: System::Windows::Forms::RadioButton^  scroll_down;
    private: System::Windows::Forms::RadioButton^  scroll_up;














    private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->components = (gcnew System::ComponentModel::Container());
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Paladin::typeid));
            this->Tabs = (gcnew System::Windows::Forms::TabControl());
            this->keys = (gcnew System::Windows::Forms::TabPage());
            this->misc = (gcnew System::Windows::Forms::TabPage());
            this->aimrcs = (gcnew System::Windows::Forms::TabPage());
            this->trig = (gcnew System::Windows::Forms::TabPage());
            this->setting = (gcnew System::Windows::Forms::TabPage());
            this->tooltips = (gcnew System::Windows::Forms::ToolTip(this->components));
            this->HitSound_p = (gcnew System::Windows::Forms::Panel());
            this->enabled_hit = (gcnew System::Windows::Forms::CheckBox());
            this->smooth_p = (gcnew System::Windows::Forms::Panel());
            this->enabled_smooth = (gcnew System::Windows::Forms::CheckBox());
            this->HitSound_L = (gcnew System::Windows::Forms::Label());
            this->smooth_l = (gcnew System::Windows::Forms::Label());
            this->hitsound_dur_s = (gcnew System::Windows::Forms::TrackBar());
            this->hitsound_freq_s = (gcnew System::Windows::Forms::TrackBar());
            this->smooth_max_s = (gcnew System::Windows::Forms::TrackBar());
            this->smooth_min_s = (gcnew System::Windows::Forms::TrackBar());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->keybind_l = (gcnew System::Windows::Forms::Label());
            this->keyexit_L = (gcnew System::Windows::Forms::Label());
            this->reload_L = (gcnew System::Windows::Forms::Label());
            this->aim_L = (gcnew System::Windows::Forms::Label());
            this->trig_L = (gcnew System::Windows::Forms::Label());
            this->bhop_L = (gcnew System::Windows::Forms::Label());
            this->bunny_p = (gcnew System::Windows::Forms::Panel());
            this->next_delay_jump = (gcnew System::Windows::Forms::TrackBar());
            this->hitchance = (gcnew System::Windows::Forms::TrackBar());
            this->bunny_L = (gcnew System::Windows::Forms::Label());
            this->enabled_bhop = (gcnew System::Windows::Forms::CheckBox());
            this->slow_p = (gcnew System::Windows::Forms::Panel());
            this->slowfactor = (gcnew System::Windows::Forms::TrackBar());
            this->slowaim_l = (gcnew System::Windows::Forms::Label());
            this->slow_enabled = (gcnew System::Windows::Forms::CheckBox());
            this->scroll_up = (gcnew System::Windows::Forms::RadioButton());
            this->scroll_down = (gcnew System::Windows::Forms::RadioButton());
            this->Tabs->SuspendLayout();
            this->keys->SuspendLayout();
            this->misc->SuspendLayout();
            this->HitSound_p->SuspendLayout();
            this->smooth_p->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitsound_dur_s))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitsound_freq_s))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->smooth_max_s))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->smooth_min_s))->BeginInit();
            this->panel1->SuspendLayout();
            this->bunny_p->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->next_delay_jump))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitchance))->BeginInit();
            this->slow_p->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->slowfactor))->BeginInit();
            this->SuspendLayout();
            // 
            // Tabs
            // 
            this->Tabs->Controls->Add(this->keys);
            this->Tabs->Controls->Add(this->misc);
            this->Tabs->Controls->Add(this->aimrcs);
            this->Tabs->Controls->Add(this->trig);
            this->Tabs->Controls->Add(this->setting);
            this->Tabs->Location = System::Drawing::Point(12, 12);
            this->Tabs->Name = L"Tabs";
            this->Tabs->SelectedIndex = 0;
            this->Tabs->Size = System::Drawing::Size(460, 237);
            this->Tabs->SizeMode = System::Windows::Forms::TabSizeMode::FillToRight;
            this->Tabs->TabIndex = 0;
            // 
            // keys
            // 
            this->keys->Controls->Add(this->panel1);
            this->keys->Location = System::Drawing::Point(4, 22);
            this->keys->Name = L"keys";
            this->keys->Padding = System::Windows::Forms::Padding(3);
            this->keys->Size = System::Drawing::Size(452, 211);
            this->keys->TabIndex = 0;
            this->keys->Text = L"Key Binds";
            this->keys->UseVisualStyleBackColor = true;
            // 
            // misc
            // 
            this->misc->Controls->Add(this->slow_p);
            this->misc->Controls->Add(this->bunny_p);
            this->misc->Controls->Add(this->smooth_p);
            this->misc->Controls->Add(this->HitSound_p);
            this->misc->Location = System::Drawing::Point(4, 22);
            this->misc->Name = L"misc";
            this->misc->Padding = System::Windows::Forms::Padding(3);
            this->misc->Size = System::Drawing::Size(452, 211);
            this->misc->TabIndex = 1;
            this->misc->Text = L"Misc";
            this->misc->UseVisualStyleBackColor = true;
            // 
            // aimrcs
            // 
            this->aimrcs->Location = System::Drawing::Point(4, 22);
            this->aimrcs->Name = L"aimrcs";
            this->aimrcs->Size = System::Drawing::Size(452, 211);
            this->aimrcs->TabIndex = 2;
            this->aimrcs->Text = L"Aimbot / RCS";
            this->aimrcs->UseVisualStyleBackColor = true;
            // 
            // trig
            // 
            this->trig->Location = System::Drawing::Point(4, 22);
            this->trig->Name = L"trig";
            this->trig->Size = System::Drawing::Size(452, 211);
            this->trig->TabIndex = 3;
            this->trig->Text = L"Triggerbot";
            this->trig->UseVisualStyleBackColor = true;
            // 
            // setting
            // 
            this->setting->Location = System::Drawing::Point(4, 22);
            this->setting->Name = L"setting";
            this->setting->Size = System::Drawing::Size(452, 211);
            this->setting->TabIndex = 4;
            this->setting->Text = L"Settings";
            this->setting->UseVisualStyleBackColor = true;
            // 
            // tooltips
            // 
            this->tooltips->ShowAlways = true;
            // 
            // HitSound_p
            // 
            this->HitSound_p->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->HitSound_p->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->HitSound_p->Controls->Add(this->hitsound_freq_s);
            this->HitSound_p->Controls->Add(this->hitsound_dur_s);
            this->HitSound_p->Controls->Add(this->HitSound_L);
            this->HitSound_p->Controls->Add(this->enabled_hit);
            this->HitSound_p->Location = System::Drawing::Point(6, 6);
            this->HitSound_p->Name = L"HitSound_p";
            this->HitSound_p->Size = System::Drawing::Size(217, 96);
            this->HitSound_p->TabIndex = 0;
            // 
            // enabled_hit
            // 
            this->enabled_hit->AutoSize = true;
            this->enabled_hit->Location = System::Drawing::Point(7, 20);
            this->enabled_hit->Name = L"enabled_hit";
            this->enabled_hit->Size = System::Drawing::Size(64, 17);
            this->enabled_hit->TabIndex = 0;
            this->enabled_hit->Text = L"Enabled";
            this->enabled_hit->UseVisualStyleBackColor = true;
            // 
            // smooth_p
            // 
            this->smooth_p->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->smooth_p->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->smooth_p->Controls->Add(this->smooth_min_s);
            this->smooth_p->Controls->Add(this->smooth_max_s);
            this->smooth_p->Controls->Add(this->smooth_l);
            this->smooth_p->Controls->Add(this->enabled_smooth);
            this->smooth_p->Location = System::Drawing::Point(229, 6);
            this->smooth_p->Name = L"smooth_p";
            this->smooth_p->Size = System::Drawing::Size(217, 96);
            this->smooth_p->TabIndex = 1;
            // 
            // enabled_smooth
            // 
            this->enabled_smooth->AutoSize = true;
            this->enabled_smooth->Location = System::Drawing::Point(6, 20);
            this->enabled_smooth->Name = L"enabled_smooth";
            this->enabled_smooth->Size = System::Drawing::Size(64, 17);
            this->enabled_smooth->TabIndex = 0;
            this->enabled_smooth->Text = L"Enabled";
            this->enabled_smooth->UseVisualStyleBackColor = true;
            // 
            // HitSound_L
            // 
            this->HitSound_L->AutoSize = true;
            this->HitSound_L->Location = System::Drawing::Point(4, 4);
            this->HitSound_L->Name = L"HitSound_L";
            this->HitSound_L->Size = System::Drawing::Size(53, 13);
            this->HitSound_L->TabIndex = 1;
            this->HitSound_L->Text = L"Hit Sound";
            // 
            // smooth_l
            // 
            this->smooth_l->AutoSize = true;
            this->smooth_l->Location = System::Drawing::Point(3, 4);
            this->smooth_l->Name = L"smooth_l";
            this->smooth_l->Size = System::Drawing::Size(57, 13);
            this->smooth_l->TabIndex = 2;
            this->smooth_l->Text = L"Smoothing";
            // 
            // hitsound_dur_s
            // 
            this->hitsound_dur_s->Location = System::Drawing::Point(77, 4);
            this->hitsound_dur_s->Maximum = 200;
            this->hitsound_dur_s->Minimum = 10;
            this->hitsound_dur_s->Name = L"hitsound_dur_s";
            this->hitsound_dur_s->Size = System::Drawing::Size(133, 45);
            this->hitsound_dur_s->TabIndex = 2;
            this->hitsound_dur_s->TickFrequency = 10;
            this->tooltips->SetToolTip(this->hitsound_dur_s, L"Slider for Duration of Sound");
            this->hitsound_dur_s->Value = 50;
            // 
            // hitsound_freq_s
            // 
            this->hitsound_freq_s->Location = System::Drawing::Point(3, 47);
            this->hitsound_freq_s->Maximum = 3000;
            this->hitsound_freq_s->Minimum = 10;
            this->hitsound_freq_s->Name = L"hitsound_freq_s";
            this->hitsound_freq_s->Size = System::Drawing::Size(207, 45);
            this->hitsound_freq_s->TabIndex = 3;
            this->hitsound_freq_s->TickFrequency = 100;
            this->tooltips->SetToolTip(this->hitsound_freq_s, L"Slider for Pitch of Sound");
            this->hitsound_freq_s->Value = 500;
            // 
            // smooth_max_s
            // 
            this->smooth_max_s->Location = System::Drawing::Point(6, 47);
            this->smooth_max_s->Maximum = 15;
            this->smooth_max_s->Minimum = 1;
            this->smooth_max_s->Name = L"smooth_max_s";
            this->smooth_max_s->Size = System::Drawing::Size(204, 45);
            this->smooth_max_s->TabIndex = 5;
            this->tooltips->SetToolTip(this->smooth_max_s, L"Slider for Maximum Smoothness");
            this->smooth_max_s->Value = 10;
            // 
            // smooth_min_s
            // 
            this->smooth_min_s->Location = System::Drawing::Point(77, 4);
            this->smooth_min_s->Minimum = 1;
            this->smooth_min_s->Name = L"smooth_min_s";
            this->smooth_min_s->Size = System::Drawing::Size(133, 45);
            this->smooth_min_s->TabIndex = 6;
            this->tooltips->SetToolTip(this->smooth_min_s, L"Slider for Minimum Smoothness");
            this->smooth_min_s->Value = 7;
            // 
            // panel1
            // 
            this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->panel1->Controls->Add(this->bhop_L);
            this->panel1->Controls->Add(this->trig_L);
            this->panel1->Controls->Add(this->aim_L);
            this->panel1->Controls->Add(this->reload_L);
            this->panel1->Controls->Add(this->keyexit_L);
            this->panel1->Controls->Add(this->keybind_l);
            this->panel1->Location = System::Drawing::Point(6, 6);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(440, 199);
            this->panel1->TabIndex = 1;
            // 
            // keybind_l
            // 
            this->keybind_l->AutoSize = true;
            this->keybind_l->Location = System::Drawing::Point(3, 0);
            this->keybind_l->Name = L"keybind_l";
            this->keybind_l->Size = System::Drawing::Size(57, 13);
            this->keybind_l->TabIndex = 1;
            this->keybind_l->Text = L"Key Binds:";
            // 
            // keyexit_L
            // 
            this->keyexit_L->AutoSize = true;
            this->keyexit_L->Location = System::Drawing::Point(24, 21);
            this->keyexit_L->Name = L"keyexit_L";
            this->keyexit_L->Size = System::Drawing::Size(50, 13);
            this->keyexit_L->TabIndex = 2;
            this->keyexit_L->Text = L"Exit Key:";
            // 
            // reload_L
            // 
            this->reload_L->AutoSize = true;
            this->reload_L->Location = System::Drawing::Point(24, 53);
            this->reload_L->Name = L"reload_L";
            this->reload_L->Size = System::Drawing::Size(99, 13);
            this->reload_L->TabIndex = 3;
            this->reload_L->Text = L"Reload Config Key:";
            // 
            // aim_L
            // 
            this->aim_L->AutoSize = true;
            this->aim_L->Location = System::Drawing::Point(24, 88);
            this->aim_L->Name = L"aim_L";
            this->aim_L->Size = System::Drawing::Size(65, 13);
            this->aim_L->TabIndex = 4;
            this->aim_L->Text = L"Aimbot Key:";
            // 
            // trig_L
            // 
            this->trig_L->AutoSize = true;
            this->trig_L->Location = System::Drawing::Point(24, 123);
            this->trig_L->Name = L"trig_L";
            this->trig_L->Size = System::Drawing::Size(82, 13);
            this->trig_L->TabIndex = 5;
            this->trig_L->Text = L"Triggerbot Key:";
            // 
            // bhop_L
            // 
            this->bhop_L->AutoSize = true;
            this->bhop_L->Location = System::Drawing::Point(24, 160);
            this->bhop_L->Name = L"bhop_L";
            this->bhop_L->Size = System::Drawing::Size(84, 13);
            this->bhop_L->TabIndex = 6;
            this->bhop_L->Text = L"Bunny Hop Key:";
            // 
            // bunny_p
            // 
            this->bunny_p->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->bunny_p->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->bunny_p->Controls->Add(this->scroll_down);
            this->bunny_p->Controls->Add(this->scroll_up);
            this->bunny_p->Controls->Add(this->next_delay_jump);
            this->bunny_p->Controls->Add(this->hitchance);
            this->bunny_p->Controls->Add(this->bunny_L);
            this->bunny_p->Controls->Add(this->enabled_bhop);
            this->bunny_p->Location = System::Drawing::Point(229, 109);
            this->bunny_p->Name = L"bunny_p";
            this->bunny_p->Size = System::Drawing::Size(217, 96);
            this->bunny_p->TabIndex = 7;
            // 
            // next_delay_jump
            // 
            this->next_delay_jump->Location = System::Drawing::Point(77, 4);
            this->next_delay_jump->Maximum = 25;
            this->next_delay_jump->Minimum = 1;
            this->next_delay_jump->Name = L"next_delay_jump";
            this->next_delay_jump->Size = System::Drawing::Size(133, 45);
            this->next_delay_jump->TabIndex = 6;
            this->next_delay_jump->TickFrequency = 5;
            this->tooltips->SetToolTip(this->next_delay_jump, L"Minimum Delay until Next Jump");
            this->next_delay_jump->Value = 20;
            // 
            // hitchance
            // 
            this->hitchance->Location = System::Drawing::Point(77, 47);
            this->hitchance->Maximum = 100;
            this->hitchance->Minimum = 1;
            this->hitchance->Name = L"hitchance";
            this->hitchance->Size = System::Drawing::Size(133, 45);
            this->hitchance->TabIndex = 3;
            this->hitchance->TickFrequency = 3;
            this->tooltips->SetToolTip(this->hitchance, L"Change to land jump");
            this->hitchance->Value = 70;
            // 
            // bunny_L
            // 
            this->bunny_L->AutoSize = true;
            this->bunny_L->Location = System::Drawing::Point(3, 4);
            this->bunny_L->Name = L"bunny_L";
            this->bunny_L->Size = System::Drawing::Size(59, 13);
            this->bunny_L->TabIndex = 2;
            this->bunny_L->Text = L"Bunny Hop";
            // 
            // enabled_bhop
            // 
            this->enabled_bhop->AutoSize = true;
            this->enabled_bhop->Location = System::Drawing::Point(6, 20);
            this->enabled_bhop->Name = L"enabled_bhop";
            this->enabled_bhop->Size = System::Drawing::Size(64, 17);
            this->enabled_bhop->TabIndex = 0;
            this->enabled_bhop->Text = L"Enabled";
            this->enabled_bhop->UseVisualStyleBackColor = true;
            // 
            // slow_p
            // 
            this->slow_p->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->slow_p->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->slow_p->Controls->Add(this->slowfactor);
            this->slow_p->Controls->Add(this->slowaim_l);
            this->slow_p->Controls->Add(this->slow_enabled);
            this->slow_p->Location = System::Drawing::Point(6, 109);
            this->slow_p->Name = L"slow_p";
            this->slow_p->Size = System::Drawing::Size(217, 96);
            this->slow_p->TabIndex = 7;
            // 
            // slowfactor
            // 
            this->slowfactor->Location = System::Drawing::Point(3, 47);
            this->slowfactor->Maximum = 8;
            this->slowfactor->Minimum = 2;
            this->slowfactor->Name = L"slowfactor";
            this->slowfactor->Size = System::Drawing::Size(207, 45);
            this->slowfactor->TabIndex = 5;
            this->tooltips->SetToolTip(this->slowfactor, L"Slider for Slow Aim Factor");
            this->slowfactor->Value = 5;
            // 
            // slowaim_l
            // 
            this->slowaim_l->AutoSize = true;
            this->slowaim_l->Location = System::Drawing::Point(3, 4);
            this->slowaim_l->Name = L"slowaim_l";
            this->slowaim_l->Size = System::Drawing::Size(49, 13);
            this->slowaim_l->TabIndex = 2;
            this->slowaim_l->Text = L"Slow Aim";
            // 
            // slow_enabled
            // 
            this->slow_enabled->AutoSize = true;
            this->slow_enabled->Location = System::Drawing::Point(6, 20);
            this->slow_enabled->Name = L"slow_enabled";
            this->slow_enabled->Size = System::Drawing::Size(64, 17);
            this->slow_enabled->TabIndex = 0;
            this->slow_enabled->Text = L"Enabled";
            this->slow_enabled->UseVisualStyleBackColor = true;
            // 
            // scroll_up
            // 
            this->scroll_up->AutoSize = true;
            this->scroll_up->Location = System::Drawing::Point(6, 66);
            this->scroll_up->Name = L"scroll_up";
            this->scroll_up->Size = System::Drawing::Size(66, 17);
            this->scroll_up->TabIndex = 7;
            this->scroll_up->TabStop = true;
            this->scroll_up->Text = L"Scroll Up";
            this->tooltips->SetToolTip(this->scroll_up, L"Scroll Direction for Bunny Hop");
            this->scroll_up->UseVisualStyleBackColor = true;
            // 
            // scroll_down
            // 
            this->scroll_down->AutoSize = true;
            this->scroll_down->Location = System::Drawing::Point(6, 43);
            this->scroll_down->Name = L"scroll_down";
            this->scroll_down->Size = System::Drawing::Size(80, 17);
            this->scroll_down->TabIndex = 8;
            this->scroll_down->TabStop = true;
            this->scroll_down->Text = L"Scroll Down";
            this->tooltips->SetToolTip(this->scroll_down, L"Scroll Direction for Bunny Hop");
            this->scroll_down->UseVisualStyleBackColor = true;
            // 
            // Paladin
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(484, 261);
            this->Controls->Add(this->Tabs);
            this->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->MaximizeBox = false;
            this->Name = L"Paladin";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Paladin";
            this->Tabs->ResumeLayout(false);
            this->keys->ResumeLayout(false);
            this->misc->ResumeLayout(false);
            this->HitSound_p->ResumeLayout(false);
            this->HitSound_p->PerformLayout();
            this->smooth_p->ResumeLayout(false);
            this->smooth_p->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitsound_dur_s))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitsound_freq_s))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->smooth_max_s))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->smooth_min_s))->EndInit();
            this->panel1->ResumeLayout(false);
            this->panel1->PerformLayout();
            this->bunny_p->ResumeLayout(false);
            this->bunny_p->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->next_delay_jump))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitchance))->EndInit();
            this->slow_p->ResumeLayout(false);
            this->slow_p->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->slowfactor))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
	};
}
