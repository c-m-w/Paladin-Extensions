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

    private: System::Windows::Forms::ToolTip^  tooltips;
    private: System::Windows::Forms::Panel^  HitSound_p;

    private: System::Windows::Forms::CheckBox^  enabled_hit;
    private: System::Windows::Forms::Panel^  smooth_p;


    private: System::Windows::Forms::CheckBox^  enabled_smooth;
    private: System::Windows::Forms::Label^  smooth_l;
    private: System::Windows::Forms::Label^  HitSound_L;
    private: System::Windows::Forms::TrackBar^  hitsound_freq_s;

    private: System::Windows::Forms::TrackBar^  hitsound_dur_s;
    private: System::Windows::Forms::Panel^  key_panel;

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
    private: System::Windows::Forms::Panel^  panel2;
    private: System::Windows::Forms::TrackBar^  trackBar2;
    private: System::Windows::Forms::TrackBar^  displace_aim;
    private: System::Windows::Forms::Label^  aim_le;
    private: System::Windows::Forms::CheckBox^  enable_aim;
    private: System::Windows::Forms::Button^  bhopKeyButton;
    private: System::Windows::Forms::Button^  trigKeyButton;
    private: System::Windows::Forms::Button^  aimKeyButton;
    private: System::Windows::Forms::Button^  reloadKeyButton;
    private: System::Windows::Forms::Button^  exitKeyButton;
    private: System::Windows::Forms::Label^  slowfac_l;
    private: System::Windows::Forms::Label^  hitchance_l;
    private: System::Windows::Forms::Label^  next_jump_l;
    private: System::Windows::Forms::Label^  smooth_max_l;
    private: System::Windows::Forms::Label^  smooth_min_l;
    private: System::Windows::Forms::Label^  hitsound_freq_l;
    private: System::Windows::Forms::Label^  hitsoud_dur_l;
    private: System::Windows::Forms::TextBox^  bone_tb;
    private: System::Windows::Forms::Panel^  panel3;
    private: System::Windows::Forms::TextBox^  textBox1;
    private: System::Windows::Forms::TrackBar^  trackBar1;
    private: System::Windows::Forms::TrackBar^  trackBar3;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::CheckBox^  checkBox1;




    private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Button^  button4;















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
            this->key_panel = (gcnew System::Windows::Forms::Panel());
            this->bhopKeyButton = (gcnew System::Windows::Forms::Button());
            this->trigKeyButton = (gcnew System::Windows::Forms::Button());
            this->aimKeyButton = (gcnew System::Windows::Forms::Button());
            this->reloadKeyButton = (gcnew System::Windows::Forms::Button());
            this->exitKeyButton = (gcnew System::Windows::Forms::Button());
            this->bhop_L = (gcnew System::Windows::Forms::Label());
            this->trig_L = (gcnew System::Windows::Forms::Label());
            this->aim_L = (gcnew System::Windows::Forms::Label());
            this->reload_L = (gcnew System::Windows::Forms::Label());
            this->keyexit_L = (gcnew System::Windows::Forms::Label());
            this->keybind_l = (gcnew System::Windows::Forms::Label());
            this->misc = (gcnew System::Windows::Forms::TabPage());
            this->slow_p = (gcnew System::Windows::Forms::Panel());
            this->slowfac_l = (gcnew System::Windows::Forms::Label());
            this->slowfactor = (gcnew System::Windows::Forms::TrackBar());
            this->slowaim_l = (gcnew System::Windows::Forms::Label());
            this->slow_enabled = (gcnew System::Windows::Forms::CheckBox());
            this->bunny_p = (gcnew System::Windows::Forms::Panel());
            this->hitchance_l = (gcnew System::Windows::Forms::Label());
            this->next_jump_l = (gcnew System::Windows::Forms::Label());
            this->scroll_down = (gcnew System::Windows::Forms::RadioButton());
            this->scroll_up = (gcnew System::Windows::Forms::RadioButton());
            this->next_delay_jump = (gcnew System::Windows::Forms::TrackBar());
            this->hitchance = (gcnew System::Windows::Forms::TrackBar());
            this->bunny_L = (gcnew System::Windows::Forms::Label());
            this->enabled_bhop = (gcnew System::Windows::Forms::CheckBox());
            this->smooth_p = (gcnew System::Windows::Forms::Panel());
            this->smooth_max_l = (gcnew System::Windows::Forms::Label());
            this->smooth_min_l = (gcnew System::Windows::Forms::Label());
            this->smooth_min_s = (gcnew System::Windows::Forms::TrackBar());
            this->smooth_max_s = (gcnew System::Windows::Forms::TrackBar());
            this->smooth_l = (gcnew System::Windows::Forms::Label());
            this->enabled_smooth = (gcnew System::Windows::Forms::CheckBox());
            this->HitSound_p = (gcnew System::Windows::Forms::Panel());
            this->hitsound_freq_l = (gcnew System::Windows::Forms::Label());
            this->hitsoud_dur_l = (gcnew System::Windows::Forms::Label());
            this->hitsound_freq_s = (gcnew System::Windows::Forms::TrackBar());
            this->hitsound_dur_s = (gcnew System::Windows::Forms::TrackBar());
            this->HitSound_L = (gcnew System::Windows::Forms::Label());
            this->enabled_hit = (gcnew System::Windows::Forms::CheckBox());
            this->aimrcs = (gcnew System::Windows::Forms::TabPage());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            this->bone_tb = (gcnew System::Windows::Forms::TextBox());
            this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
            this->displace_aim = (gcnew System::Windows::Forms::TrackBar());
            this->aim_le = (gcnew System::Windows::Forms::Label());
            this->enable_aim = (gcnew System::Windows::Forms::CheckBox());
            this->trig = (gcnew System::Windows::Forms::TabPage());
            this->panel3 = (gcnew System::Windows::Forms::Panel());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
            this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
            this->tooltips = (gcnew System::Windows::Forms::ToolTip(this->components));
            this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->Tabs->SuspendLayout();
            this->keys->SuspendLayout();
            this->key_panel->SuspendLayout();
            this->misc->SuspendLayout();
            this->slow_p->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->slowfactor))->BeginInit();
            this->bunny_p->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->next_delay_jump))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitchance))->BeginInit();
            this->smooth_p->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->smooth_min_s))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->smooth_max_s))->BeginInit();
            this->HitSound_p->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitsound_freq_s))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitsound_dur_s))->BeginInit();
            this->aimrcs->SuspendLayout();
            this->panel2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->displace_aim))->BeginInit();
            this->trig->SuspendLayout();
            this->panel3->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
            this->SuspendLayout();
            // 
            // Tabs
            // 
            this->Tabs->Controls->Add(this->keys);
            this->Tabs->Controls->Add(this->misc);
            this->Tabs->Controls->Add(this->aimrcs);
            this->Tabs->Controls->Add(this->trig);
            this->Tabs->Location = System::Drawing::Point(12, 12);
            this->Tabs->Name = L"Tabs";
            this->Tabs->SelectedIndex = 0;
            this->Tabs->Size = System::Drawing::Size(460, 237);
            this->Tabs->SizeMode = System::Windows::Forms::TabSizeMode::FillToRight;
            this->Tabs->TabIndex = 0;
            // 
            // keys
            // 
            this->keys->Controls->Add(this->key_panel);
            this->keys->Location = System::Drawing::Point(4, 22);
            this->keys->Name = L"keys";
            this->keys->Padding = System::Windows::Forms::Padding(3);
            this->keys->Size = System::Drawing::Size(452, 211);
            this->keys->TabIndex = 0;
            this->keys->Text = L"Key Binds";
            this->keys->UseVisualStyleBackColor = true;
            // 
            // key_panel
            // 
            this->key_panel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->key_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->key_panel->Controls->Add(this->button1);
            this->key_panel->Controls->Add(this->button4);
            this->key_panel->Controls->Add(this->bhopKeyButton);
            this->key_panel->Controls->Add(this->trigKeyButton);
            this->key_panel->Controls->Add(this->aimKeyButton);
            this->key_panel->Controls->Add(this->reloadKeyButton);
            this->key_panel->Controls->Add(this->exitKeyButton);
            this->key_panel->Controls->Add(this->bhop_L);
            this->key_panel->Controls->Add(this->trig_L);
            this->key_panel->Controls->Add(this->aim_L);
            this->key_panel->Controls->Add(this->reload_L);
            this->key_panel->Controls->Add(this->keyexit_L);
            this->key_panel->Controls->Add(this->keybind_l);
            this->key_panel->Location = System::Drawing::Point(6, 6);
            this->key_panel->Name = L"key_panel";
            this->key_panel->Size = System::Drawing::Size(440, 199);
            this->key_panel->TabIndex = 1;
            // 
            // bhopKeyButton
            // 
            this->bhopKeyButton->Location = System::Drawing::Point(157, 137);
            this->bhopKeyButton->Name = L"bhopKeyButton";
            this->bhopKeyButton->Size = System::Drawing::Size(275, 23);
            this->bhopKeyButton->TabIndex = 11;
            this->bhopKeyButton->Text = L"Click to bind a key (Current: 0)";
            this->bhopKeyButton->UseVisualStyleBackColor = true;
            // 
            // trigKeyButton
            // 
            this->trigKeyButton->Location = System::Drawing::Point(157, 109);
            this->trigKeyButton->Name = L"trigKeyButton";
            this->trigKeyButton->Size = System::Drawing::Size(275, 23);
            this->trigKeyButton->TabIndex = 10;
            this->trigKeyButton->Text = L"Click to bind a key (Current: 0)";
            this->trigKeyButton->UseVisualStyleBackColor = true;
            // 
            // aimKeyButton
            // 
            this->aimKeyButton->Location = System::Drawing::Point(157, 80);
            this->aimKeyButton->Name = L"aimKeyButton";
            this->aimKeyButton->Size = System::Drawing::Size(275, 23);
            this->aimKeyButton->TabIndex = 9;
            this->aimKeyButton->Text = L"Click to bind a key (Current: 0)";
            this->aimKeyButton->UseVisualStyleBackColor = true;
            // 
            // reloadKeyButton
            // 
            this->reloadKeyButton->Location = System::Drawing::Point(157, 52);
            this->reloadKeyButton->Name = L"reloadKeyButton";
            this->reloadKeyButton->Size = System::Drawing::Size(275, 23);
            this->reloadKeyButton->TabIndex = 8;
            this->reloadKeyButton->Text = L"Click to bind a key (Current: 0)";
            this->reloadKeyButton->UseVisualStyleBackColor = true;
            // 
            // exitKeyButton
            // 
            this->exitKeyButton->Location = System::Drawing::Point(157, 23);
            this->exitKeyButton->Name = L"exitKeyButton";
            this->exitKeyButton->Size = System::Drawing::Size(275, 23);
            this->exitKeyButton->TabIndex = 7;
            this->exitKeyButton->Text = L"Click to bind a key (Current: 0)";
            this->exitKeyButton->UseVisualStyleBackColor = true;
            // 
            // bhop_L
            // 
            this->bhop_L->AutoSize = true;
            this->bhop_L->Location = System::Drawing::Point(24, 142);
            this->bhop_L->Name = L"bhop_L";
            this->bhop_L->Size = System::Drawing::Size(84, 13);
            this->bhop_L->TabIndex = 6;
            this->bhop_L->Text = L"Bunny Hop Key:";
            // 
            // trig_L
            // 
            this->trig_L->AutoSize = true;
            this->trig_L->Location = System::Drawing::Point(24, 114);
            this->trig_L->Name = L"trig_L";
            this->trig_L->Size = System::Drawing::Size(82, 13);
            this->trig_L->TabIndex = 5;
            this->trig_L->Text = L"Triggerbot Key:";
            // 
            // aim_L
            // 
            this->aim_L->AutoSize = true;
            this->aim_L->Location = System::Drawing::Point(24, 85);
            this->aim_L->Name = L"aim_L";
            this->aim_L->Size = System::Drawing::Size(65, 13);
            this->aim_L->TabIndex = 4;
            this->aim_L->Text = L"Aimbot Key:";
            // 
            // reload_L
            // 
            this->reload_L->AutoSize = true;
            this->reload_L->Location = System::Drawing::Point(24, 57);
            this->reload_L->Name = L"reload_L";
            this->reload_L->Size = System::Drawing::Size(99, 13);
            this->reload_L->TabIndex = 3;
            this->reload_L->Text = L"Reload Config Key:";
            // 
            // keyexit_L
            // 
            this->keyexit_L->AutoSize = true;
            this->keyexit_L->Location = System::Drawing::Point(24, 28);
            this->keyexit_L->Name = L"keyexit_L";
            this->keyexit_L->Size = System::Drawing::Size(50, 13);
            this->keyexit_L->TabIndex = 2;
            this->keyexit_L->Text = L"Exit Key:";
            // 
            // keybind_l
            // 
            this->keybind_l->AutoSize = true;
            this->keybind_l->Location = System::Drawing::Point(3, 3);
            this->keybind_l->Name = L"keybind_l";
            this->keybind_l->Size = System::Drawing::Size(57, 13);
            this->keybind_l->TabIndex = 1;
            this->keybind_l->Text = L"Key Binds:";
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
            // slow_p
            // 
            this->slow_p->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->slow_p->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->slow_p->Controls->Add(this->slowfac_l);
            this->slow_p->Controls->Add(this->slowfactor);
            this->slow_p->Controls->Add(this->slowaim_l);
            this->slow_p->Controls->Add(this->slow_enabled);
            this->slow_p->Location = System::Drawing::Point(6, 109);
            this->slow_p->Name = L"slow_p";
            this->slow_p->Size = System::Drawing::Size(217, 96);
            this->slow_p->TabIndex = 7;
            // 
            // slowfac_l
            // 
            this->slowfac_l->AutoSize = true;
            this->slowfac_l->Location = System::Drawing::Point(8, 73);
            this->slowfac_l->Name = L"slowfac_l";
            this->slowfac_l->Size = System::Drawing::Size(32, 13);
            this->slowfac_l->TabIndex = 6;
            this->slowfac_l->Text = L"1/2 x";
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
            this->slowfactor->Value = 2;
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
            // bunny_p
            // 
            this->bunny_p->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->bunny_p->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->bunny_p->Controls->Add(this->hitchance_l);
            this->bunny_p->Controls->Add(this->next_jump_l);
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
            // hitchance_l
            // 
            this->hitchance_l->AutoSize = true;
            this->hitchance_l->Location = System::Drawing::Point(82, 73);
            this->hitchance_l->Name = L"hitchance_l";
            this->hitchance_l->Size = System::Drawing::Size(33, 13);
            this->hitchance_l->TabIndex = 9;
            this->hitchance_l->Text = L"70 %";
            // 
            // next_jump_l
            // 
            this->next_jump_l->AutoSize = true;
            this->next_jump_l->Location = System::Drawing::Point(82, 30);
            this->next_jump_l->Name = L"next_jump_l";
            this->next_jump_l->Size = System::Drawing::Size(35, 13);
            this->next_jump_l->TabIndex = 8;
            this->next_jump_l->Text = L"20 ms";
            // 
            // scroll_down
            // 
            this->scroll_down->AutoSize = true;
            this->scroll_down->Checked = true;
            this->scroll_down->Location = System::Drawing::Point(6, 43);
            this->scroll_down->Name = L"scroll_down";
            this->scroll_down->Size = System::Drawing::Size(80, 17);
            this->scroll_down->TabIndex = 8;
            this->scroll_down->TabStop = true;
            this->scroll_down->Text = L"Scroll Down";
            this->tooltips->SetToolTip(this->scroll_down, L"Scroll Direction for Bunny Hop");
            this->scroll_down->UseVisualStyleBackColor = true;
            // 
            // scroll_up
            // 
            this->scroll_up->AutoSize = true;
            this->scroll_up->Location = System::Drawing::Point(6, 66);
            this->scroll_up->Name = L"scroll_up";
            this->scroll_up->Size = System::Drawing::Size(66, 17);
            this->scroll_up->TabIndex = 7;
            this->scroll_up->Text = L"Scroll Up";
            this->tooltips->SetToolTip(this->scroll_up, L"Scroll Direction for Bunny Hop");
            this->scroll_up->UseVisualStyleBackColor = true;
            // 
            // next_delay_jump
            // 
            this->next_delay_jump->Location = System::Drawing::Point(78, 4);
            this->next_delay_jump->Maximum = 25;
            this->next_delay_jump->Minimum = 1;
            this->next_delay_jump->Name = L"next_delay_jump";
            this->next_delay_jump->Size = System::Drawing::Size(132, 45);
            this->next_delay_jump->TabIndex = 6;
            this->next_delay_jump->TickFrequency = 5;
            this->tooltips->SetToolTip(this->next_delay_jump, L"Minimum Delay until Next Jump");
            this->next_delay_jump->Value = 20;
            // 
            // hitchance
            // 
            this->hitchance->Location = System::Drawing::Point(78, 47);
            this->hitchance->Maximum = 100;
            this->hitchance->Minimum = 1;
            this->hitchance->Name = L"hitchance";
            this->hitchance->Size = System::Drawing::Size(132, 45);
            this->hitchance->TabIndex = 3;
            this->hitchance->TickFrequency = 5;
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
            // smooth_p
            // 
            this->smooth_p->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->smooth_p->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->smooth_p->Controls->Add(this->smooth_max_l);
            this->smooth_p->Controls->Add(this->smooth_min_l);
            this->smooth_p->Controls->Add(this->smooth_min_s);
            this->smooth_p->Controls->Add(this->smooth_max_s);
            this->smooth_p->Controls->Add(this->smooth_l);
            this->smooth_p->Controls->Add(this->enabled_smooth);
            this->smooth_p->Location = System::Drawing::Point(229, 6);
            this->smooth_p->Name = L"smooth_p";
            this->smooth_p->Size = System::Drawing::Size(217, 96);
            this->smooth_p->TabIndex = 1;
            // 
            // smooth_max_l
            // 
            this->smooth_max_l->AutoSize = true;
            this->smooth_max_l->Location = System::Drawing::Point(8, 73);
            this->smooth_max_l->Name = L"smooth_max_l";
            this->smooth_max_l->Size = System::Drawing::Size(28, 13);
            this->smooth_max_l->TabIndex = 7;
            this->smooth_max_l->Text = L"10 x";
            // 
            // smooth_min_l
            // 
            this->smooth_min_l->AutoSize = true;
            this->smooth_min_l->Location = System::Drawing::Point(82, 30);
            this->smooth_min_l->Name = L"smooth_min_l";
            this->smooth_min_l->Size = System::Drawing::Size(22, 13);
            this->smooth_min_l->TabIndex = 6;
            this->smooth_min_l->Text = L"7 x";
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
            // smooth_max_s
            // 
            this->smooth_max_s->Location = System::Drawing::Point(3, 47);
            this->smooth_max_s->Maximum = 15;
            this->smooth_max_s->Minimum = 1;
            this->smooth_max_s->Name = L"smooth_max_s";
            this->smooth_max_s->Size = System::Drawing::Size(207, 45);
            this->smooth_max_s->TabIndex = 5;
            this->tooltips->SetToolTip(this->smooth_max_s, L"Slider for Maximum Smoothness");
            this->smooth_max_s->Value = 10;
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
            // HitSound_p
            // 
            this->HitSound_p->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->HitSound_p->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->HitSound_p->Controls->Add(this->hitsound_freq_l);
            this->HitSound_p->Controls->Add(this->hitsoud_dur_l);
            this->HitSound_p->Controls->Add(this->hitsound_freq_s);
            this->HitSound_p->Controls->Add(this->hitsound_dur_s);
            this->HitSound_p->Controls->Add(this->HitSound_L);
            this->HitSound_p->Controls->Add(this->enabled_hit);
            this->HitSound_p->Location = System::Drawing::Point(6, 6);
            this->HitSound_p->Name = L"HitSound_p";
            this->HitSound_p->Size = System::Drawing::Size(217, 96);
            this->HitSound_p->TabIndex = 0;
            // 
            // hitsound_freq_l
            // 
            this->hitsound_freq_l->AutoSize = true;
            this->hitsound_freq_l->Location = System::Drawing::Point(8, 73);
            this->hitsound_freq_l->Name = L"hitsound_freq_l";
            this->hitsound_freq_l->Size = System::Drawing::Size(39, 13);
            this->hitsound_freq_l->TabIndex = 5;
            this->hitsound_freq_l->Text = L"300 hz";
            // 
            // hitsoud_dur_l
            // 
            this->hitsoud_dur_l->AutoSize = true;
            this->hitsoud_dur_l->Location = System::Drawing::Point(82, 30);
            this->hitsoud_dur_l->Name = L"hitsoud_dur_l";
            this->hitsoud_dur_l->Size = System::Drawing::Size(35, 13);
            this->hitsoud_dur_l->TabIndex = 4;
            this->hitsoud_dur_l->Text = L"50 ms";
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
            // HitSound_L
            // 
            this->HitSound_L->AutoSize = true;
            this->HitSound_L->Location = System::Drawing::Point(4, 4);
            this->HitSound_L->Name = L"HitSound_L";
            this->HitSound_L->Size = System::Drawing::Size(53, 13);
            this->HitSound_L->TabIndex = 1;
            this->HitSound_L->Text = L"Hit Sound";
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
            // aimrcs
            // 
            this->aimrcs->Controls->Add(this->panel2);
            this->aimrcs->Location = System::Drawing::Point(4, 22);
            this->aimrcs->Name = L"aimrcs";
            this->aimrcs->Size = System::Drawing::Size(452, 211);
            this->aimrcs->TabIndex = 2;
            this->aimrcs->Text = L"Aimbot / RCS";
            this->aimrcs->UseVisualStyleBackColor = true;
            // 
            // panel2
            // 
            this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->panel2->Controls->Add(this->bone_tb);
            this->panel2->Controls->Add(this->trackBar2);
            this->panel2->Controls->Add(this->displace_aim);
            this->panel2->Controls->Add(this->aim_le);
            this->panel2->Controls->Add(this->enable_aim);
            this->panel2->Location = System::Drawing::Point(6, 6);
            this->panel2->Name = L"panel2";
            this->panel2->Size = System::Drawing::Size(217, 199);
            this->panel2->TabIndex = 1;
            // 
            // bone_tb
            // 
            this->bone_tb->Location = System::Drawing::Point(10, 43);
            this->bone_tb->MaxLength = 2;
            this->bone_tb->Name = L"bone_tb";
            this->bone_tb->Size = System::Drawing::Size(193, 21);
            this->bone_tb->TabIndex = 5;
            this->bone_tb->Text = L"8";
            this->bone_tb->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->tooltips->SetToolTip(this->bone_tb, L"Bone to aim to");
            // 
            // trackBar2
            // 
            this->trackBar2->Location = System::Drawing::Point(3, 147);
            this->trackBar2->Maximum = 3000;
            this->trackBar2->Minimum = 10;
            this->trackBar2->Name = L"trackBar2";
            this->trackBar2->Size = System::Drawing::Size(207, 45);
            this->trackBar2->TabIndex = 4;
            this->trackBar2->TickFrequency = 100;
            this->tooltips->SetToolTip(this->trackBar2, L"Slider for Pitch of Sound");
            this->trackBar2->Value = 500;
            // 
            // displace_aim
            // 
            this->displace_aim->Location = System::Drawing::Point(3, 78);
            this->displace_aim->Minimum = -10;
            this->displace_aim->Name = L"displace_aim";
            this->displace_aim->Size = System::Drawing::Size(207, 45);
            this->displace_aim->TabIndex = 3;
            this->tooltips->SetToolTip(this->displace_aim, L"Vertical Displacement for Aimbot");
            // 
            // aim_le
            // 
            this->aim_le->AutoSize = true;
            this->aim_le->Location = System::Drawing::Point(4, 4);
            this->aim_le->Name = L"aim_le";
            this->aim_le->Size = System::Drawing::Size(40, 13);
            this->aim_le->TabIndex = 1;
            this->aim_le->Text = L"Aimbot";
            // 
            // enable_aim
            // 
            this->enable_aim->AutoSize = true;
            this->enable_aim->Location = System::Drawing::Point(7, 20);
            this->enable_aim->Name = L"enable_aim";
            this->enable_aim->Size = System::Drawing::Size(64, 17);
            this->enable_aim->TabIndex = 0;
            this->enable_aim->Text = L"Enabled";
            this->enable_aim->UseVisualStyleBackColor = true;
            // 
            // trig
            // 
            this->trig->Controls->Add(this->panel3);
            this->trig->Location = System::Drawing::Point(4, 22);
            this->trig->Name = L"trig";
            this->trig->Size = System::Drawing::Size(452, 211);
            this->trig->TabIndex = 3;
            this->trig->Text = L"Triggerbot";
            this->trig->UseVisualStyleBackColor = true;
            // 
            // panel3
            // 
            this->panel3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
                static_cast<System::Int32>(static_cast<System::Byte>(32)));
            this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->panel3->Controls->Add(this->textBox1);
            this->panel3->Controls->Add(this->trackBar1);
            this->panel3->Controls->Add(this->trackBar3);
            this->panel3->Controls->Add(this->label1);
            this->panel3->Controls->Add(this->checkBox1);
            this->panel3->Location = System::Drawing::Point(6, 6);
            this->panel3->Name = L"panel3";
            this->panel3->Size = System::Drawing::Size(440, 199);
            this->panel3->TabIndex = 2;
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(10, 43);
            this->textBox1->MaxLength = 2;
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(193, 21);
            this->textBox1->TabIndex = 5;
            this->textBox1->Text = L"8";
            this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->tooltips->SetToolTip(this->textBox1, L"Bone to aim to");
            // 
            // trackBar1
            // 
            this->trackBar1->Location = System::Drawing::Point(3, 147);
            this->trackBar1->Maximum = 3000;
            this->trackBar1->Minimum = 10;
            this->trackBar1->Name = L"trackBar1";
            this->trackBar1->Size = System::Drawing::Size(207, 45);
            this->trackBar1->TabIndex = 4;
            this->trackBar1->TickFrequency = 100;
            this->tooltips->SetToolTip(this->trackBar1, L"Slider for Pitch of Sound");
            this->trackBar1->Value = 500;
            // 
            // trackBar3
            // 
            this->trackBar3->Location = System::Drawing::Point(3, 78);
            this->trackBar3->Minimum = -10;
            this->trackBar3->Name = L"trackBar3";
            this->trackBar3->Size = System::Drawing::Size(207, 45);
            this->trackBar3->TabIndex = 3;
            this->tooltips->SetToolTip(this->trackBar3, L"Vertical Displacement for Aimbot");
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(4, 4);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(40, 13);
            this->label1->TabIndex = 1;
            this->label1->Text = L"Aimbot";
            // 
            // checkBox1
            // 
            this->checkBox1->AutoSize = true;
            this->checkBox1->Location = System::Drawing::Point(7, 20);
            this->checkBox1->Name = L"checkBox1";
            this->checkBox1->Size = System::Drawing::Size(64, 17);
            this->checkBox1->TabIndex = 0;
            this->checkBox1->Text = L"Enabled";
            this->checkBox1->UseVisualStyleBackColor = true;
            // 
            // tooltips
            // 
            this->tooltips->ShowAlways = true;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(357, 168);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(75, 23);
            this->button1->TabIndex = 13;
            this->button1->Text = L"Undo";
            this->button1->UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this->button4->Location = System::Drawing::Point(276, 168);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(75, 23);
            this->button4->TabIndex = 12;
            this->button4->Text = L"Save";
            this->button4->UseVisualStyleBackColor = true;
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
            this->key_panel->ResumeLayout(false);
            this->key_panel->PerformLayout();
            this->misc->ResumeLayout(false);
            this->slow_p->ResumeLayout(false);
            this->slow_p->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->slowfactor))->EndInit();
            this->bunny_p->ResumeLayout(false);
            this->bunny_p->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->next_delay_jump))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitchance))->EndInit();
            this->smooth_p->ResumeLayout(false);
            this->smooth_p->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->smooth_min_s))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->smooth_max_s))->EndInit();
            this->HitSound_p->ResumeLayout(false);
            this->HitSound_p->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitsound_freq_s))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hitsound_dur_s))->EndInit();
            this->aimrcs->ResumeLayout(false);
            this->panel2->ResumeLayout(false);
            this->panel2->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->displace_aim))->EndInit();
            this->trig->ResumeLayout(false);
            this->panel3->ResumeLayout(false);
            this->panel3->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
	};
}
