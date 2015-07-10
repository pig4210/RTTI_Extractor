#pragma once

namespace RTTI_Extractor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// dlg 摘要
	/// </summary>
	public ref class dlg : public System::Windows::Forms::Form
	{
	public:
		dlg(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~dlg()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::TextBox^  TB_Start;
  protected:
  private: System::Windows::Forms::GroupBox^  GB_Main;
  private: System::Windows::Forms::Button^  Btn_Match;
  private: System::Windows::Forms::TextBox^  TB_Len;

  private: System::Windows::Forms::Label^  LB_Len;
  private: System::Windows::Forms::Label^  LB_Start;
  public: System::Windows::Forms::TextBox^  TB_mem;
  private: System::Windows::Forms::Button^  Btn_Close;
  public:
  private: System::Windows::Forms::Button^  Btn_Min;
  private: System::Windows::Forms::Label^  LB_Pos;
  private: System::Windows::Forms::ToolTip^  tp;
  private: System::Windows::Forms::CheckBox^  CB_More;
  private: System::Windows::Forms::CheckBox^  CB_STL;


  private: System::ComponentModel::IContainer^  components;

  private:

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
    this->components = (gcnew System::ComponentModel::Container());
    System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(dlg::typeid));
    this->TB_Start = (gcnew System::Windows::Forms::TextBox());
    this->GB_Main = (gcnew System::Windows::Forms::GroupBox());
    this->CB_STL = (gcnew System::Windows::Forms::CheckBox());
    this->TB_Len = (gcnew System::Windows::Forms::TextBox());
    this->CB_More = (gcnew System::Windows::Forms::CheckBox());
    this->Btn_Match = (gcnew System::Windows::Forms::Button());
    this->LB_Len = (gcnew System::Windows::Forms::Label());
    this->LB_Start = (gcnew System::Windows::Forms::Label());
    this->TB_mem = (gcnew System::Windows::Forms::TextBox());
    this->Btn_Close = (gcnew System::Windows::Forms::Button());
    this->Btn_Min = (gcnew System::Windows::Forms::Button());
    this->LB_Pos = (gcnew System::Windows::Forms::Label());
    this->tp = (gcnew System::Windows::Forms::ToolTip(this->components));
    this->GB_Main->SuspendLayout();
    this->SuspendLayout();
    // 
    // TB_Start
    // 
    this->TB_Start->BackColor = System::Drawing::Color::Silver;
    this->TB_Start->BorderStyle = System::Windows::Forms::BorderStyle::None;
    this->TB_Start->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
    this->TB_Start->ForeColor = System::Drawing::Color::Black;
    this->TB_Start->Location = System::Drawing::Point(48, 19);
    this->TB_Start->MaxLength = 25;
    this->TB_Start->Name = L"TB_Start";
    this->TB_Start->Size = System::Drawing::Size(154, 14);
    this->TB_Start->TabIndex = 1;
    this->TB_Start->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
    this->tp->SetToolTip(this->TB_Start, L"需要解析的内存起始位置");
    this->TB_Start->TextChanged += gcnew System::EventHandler(this, &dlg::TB_Start_TextChanged);
    // 
    // GB_Main
    // 
    this->GB_Main->Controls->Add(this->CB_STL);
    this->GB_Main->Controls->Add(this->TB_Len);
    this->GB_Main->Controls->Add(this->TB_Start);
    this->GB_Main->Controls->Add(this->CB_More);
    this->GB_Main->Controls->Add(this->Btn_Match);
    this->GB_Main->Controls->Add(this->LB_Len);
    this->GB_Main->Controls->Add(this->LB_Start);
    this->GB_Main->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->GB_Main->ForeColor = System::Drawing::Color::Silver;
    this->GB_Main->Location = System::Drawing::Point(0, 12);
    this->GB_Main->Name = L"GB_Main";
    this->GB_Main->Size = System::Drawing::Size(480, 42);
    this->GB_Main->TabIndex = 0;
    this->GB_Main->TabStop = false;
    this->GB_Main->Text = L"控制面板";
    // 
    // CB_STL
    // 
    this->CB_STL->AutoSize = true;
    this->CB_STL->Checked = true;
    this->CB_STL->CheckState = System::Windows::Forms::CheckState::Checked;
    this->CB_STL->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->CB_STL->Location = System::Drawing::Point(346, 18);
    this->CB_STL->Name = L"CB_STL";
    this->CB_STL->Size = System::Drawing::Size(69, 16);
    this->CB_STL->TabIndex = 6;
    this->CB_STL->Text = L"标准库 &S";
    this->tp->SetToolTip(this->CB_STL, L"解析标准库");
    this->CB_STL->UseVisualStyleBackColor = true;
    // 
    // TB_Len
    // 
    this->TB_Len->BackColor = System::Drawing::Color::Silver;
    this->TB_Len->BorderStyle = System::Windows::Forms::BorderStyle::None;
    this->TB_Len->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
    this->TB_Len->ForeColor = System::Drawing::Color::Black;
    this->TB_Len->Location = System::Drawing::Point(246, 19);
    this->TB_Len->MaxLength = 5;
    this->TB_Len->Name = L"TB_Len";
    this->TB_Len->Size = System::Drawing::Size(34, 14);
    this->TB_Len->TabIndex = 3;
    this->TB_Len->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
    this->tp->SetToolTip(this->TB_Len, L"需要解析的数据长度");
    this->TB_Len->TextChanged += gcnew System::EventHandler(this, &dlg::TB_Start_TextChanged);
    // 
    // CB_More
    // 
    this->CB_More->AutoSize = true;
    this->CB_More->Checked = true;
    this->CB_More->CheckState = System::Windows::Forms::CheckState::Checked;
    this->CB_More->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->CB_More->Location = System::Drawing::Point(286, 18);
    this->CB_More->Name = L"CB_More";
    this->CB_More->Size = System::Drawing::Size(57, 16);
    this->CB_More->TabIndex = 5;
    this->CB_More->Text = L"详细 &M";
    this->tp->SetToolTip(this->CB_More, L"解析继承的类");
    this->CB_More->UseVisualStyleBackColor = true;
    // 
    // Btn_Match
    // 
    this->Btn_Match->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
                                                                  static_cast<System::Int32>(static_cast<System::Byte>(40)));
    this->Btn_Match->FlatAppearance->BorderSize = 0;
    this->Btn_Match->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Black;
    this->Btn_Match->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
                                                                                           static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
    this->Btn_Match->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->Btn_Match->Location = System::Drawing::Point(418, 15);
    this->Btn_Match->Name = L"Btn_Match";
    this->Btn_Match->Size = System::Drawing::Size(58, 22);
    this->Btn_Match->TabIndex = 4;
    this->Btn_Match->Text = L"解析 &E";
    this->Btn_Match->UseVisualStyleBackColor = false;
    this->Btn_Match->Click += gcnew System::EventHandler(this, &dlg::Btn_Match_Click);
    // 
    // LB_Len
    // 
    this->LB_Len->AutoSize = true;
    this->LB_Len->Location = System::Drawing::Point(203, 20);
    this->LB_Len->Name = L"LB_Len";
    this->LB_Len->Size = System::Drawing::Size(41, 12);
    this->LB_Len->TabIndex = 2;
    this->LB_Len->Text = L"长度 &L";
    // 
    // LB_Start
    // 
    this->LB_Start->AutoSize = true;
    this->LB_Start->Location = System::Drawing::Point(5, 20);
    this->LB_Start->Name = L"LB_Start";
    this->LB_Start->Size = System::Drawing::Size(41, 12);
    this->LB_Start->TabIndex = 0;
    this->LB_Start->Text = L"地址 &A";
    // 
    // TB_mem
    // 
    this->TB_mem->BackColor = System::Drawing::Color::Black;
    this->TB_mem->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
    this->TB_mem->Cursor = System::Windows::Forms::Cursors::Arrow;
    this->TB_mem->Dock = System::Windows::Forms::DockStyle::Bottom;
    this->TB_mem->ForeColor = System::Drawing::Color::Silver;
    this->TB_mem->HideSelection = false;
    this->TB_mem->Location = System::Drawing::Point(0, 56);
    this->TB_mem->Multiline = true;
    this->TB_mem->Name = L"TB_mem";
    this->TB_mem->ReadOnly = true;
    this->TB_mem->ScrollBars = System::Windows::Forms::ScrollBars::Both;
    this->TB_mem->Size = System::Drawing::Size(480, 384);
    this->TB_mem->TabIndex = 1;
    this->TB_mem->WordWrap = false;
    this->TB_mem->DoubleClick += gcnew System::EventHandler(this, &dlg::TB_mem_DoubleClick);
    // 
    // Btn_Close
    // 
    this->Btn_Close->BackColor = System::Drawing::Color::Brown;
    this->Btn_Close->FlatAppearance->BorderSize = 0;
    this->Btn_Close->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Fuchsia;
    this->Btn_Close->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Red;
    this->Btn_Close->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->Btn_Close->Location = System::Drawing::Point(0, 0);
    this->Btn_Close->Name = L"Btn_Close";
    this->Btn_Close->Size = System::Drawing::Size(32, 10);
    this->Btn_Close->TabIndex = 2;
    this->Btn_Close->Text = L"&X";
    this->Btn_Close->TextAlign = System::Drawing::ContentAlignment::TopLeft;
    this->tp->SetToolTip(this->Btn_Close, L"关闭(X)");
    this->Btn_Close->UseVisualStyleBackColor = false;
    this->Btn_Close->Click += gcnew System::EventHandler(this, &dlg::Btn_Close_Click);
    // 
    // Btn_Min
    // 
    this->Btn_Min->BackColor = System::Drawing::Color::Goldenrod;
    this->Btn_Min->FlatAppearance->BorderSize = 0;
    this->Btn_Min->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Lime;
    this->Btn_Min->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Gold;
    this->Btn_Min->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->Btn_Min->Location = System::Drawing::Point(32, 0);
    this->Btn_Min->Name = L"Btn_Min";
    this->Btn_Min->Size = System::Drawing::Size(32, 10);
    this->Btn_Min->TabIndex = 3;
    this->Btn_Min->Text = L"&N";
    this->Btn_Min->TextAlign = System::Drawing::ContentAlignment::TopLeft;
    this->tp->SetToolTip(this->Btn_Min, L"最小化(N)");
    this->Btn_Min->UseVisualStyleBackColor = false;
    this->Btn_Min->Click += gcnew System::EventHandler(this, &dlg::Btn_Min_Click);
    // 
    // LB_Pos
    // 
    this->LB_Pos->BackColor = System::Drawing::Color::DimGray;
    this->LB_Pos->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
    this->LB_Pos->Location = System::Drawing::Point(64, 0);
    this->LB_Pos->Name = L"LB_Pos";
    this->LB_Pos->Size = System::Drawing::Size(416, 10);
    this->LB_Pos->TabIndex = 4;
    this->tp->SetToolTip(this->LB_Pos, L"拖拽移动窗口");
    this->LB_Pos->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &dlg::LB_Pos_MouseDown);
    // 
    // tp
    // 
    this->tp->AutomaticDelay = 0;
    this->tp->AutoPopDelay = 2000;
    this->tp->BackColor = System::Drawing::Color::Gold;
    this->tp->ForeColor = System::Drawing::Color::Black;
    this->tp->InitialDelay = 500;
    this->tp->IsBalloon = true;
    this->tp->ReshowDelay = 0;
    // 
    // dlg
    // 
    this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->BackColor = System::Drawing::Color::Black;
    this->ClientSize = System::Drawing::Size(480, 440);
    this->Controls->Add(this->Btn_Close);
    this->Controls->Add(this->Btn_Min);
    this->Controls->Add(this->LB_Pos);
    this->Controls->Add(this->TB_mem);
    this->Controls->Add(this->GB_Main);
    this->ForeColor = System::Drawing::Color::Silver;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
    this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
    this->MaximizeBox = false;
    this->Name = L"dlg";
    this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Load += gcnew System::EventHandler(this, &dlg::dlg_Load);
    this->GB_Main->ResumeLayout(false);
    this->GB_Main->PerformLayout();
    this->ResumeLayout(false);
    this->PerformLayout();

      }
#pragma endregion
  private: System::Void dlg_Load(System::Object^  sender, System::EventArgs^  e);
  private: System::Void Btn_Close_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void Btn_Min_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void LB_Pos_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
  private: System::Void TB_Start_TextChanged(System::Object^  sender, System::EventArgs^  e);
  private: System::Void Btn_Match_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void TB_mem_DoubleClick(System::Object^  sender, System::EventArgs^  e);
};
}
