#pragma once
#using<system.dll>
using namespace System;
using namespace System::IO;
namespace iDoFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	protected: 
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  SerialNumber;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Description;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  From;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  End;
	private: System::Windows::Forms::ComboBox^  comboBox1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->SerialNumber = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Description = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->From = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->End = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->SerialNumber, 
				this->Description, this->From, this->End});
			this->dataGridView1->Location = System::Drawing::Point(0, 0);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->Size = System::Drawing::Size(403, 150);
			this->dataGridView1->TabIndex = 0;
			// 
			// SerialNumber
			// 
			this->SerialNumber->HeaderText = L"SerialNumber";
			this->SerialNumber->Name = L"SerialNumber";
			this->SerialNumber->ReadOnly = true;
			// 
			// Description
			// 
			this->Description->HeaderText = L"Description";
			this->Description->Name = L"Description";
			this->Description->ReadOnly = true;
			// 
			// From
			// 
			this->From->HeaderText = L"From At";
			this->From->Name = L"From";
			this->From->ReadOnly = true;
			// 
			// End
			// 
			this->End->HeaderText = L"End";
			this->End->Name = L"End";
			this->End->ReadOnly = true;
			// 
			// comboBox1
			// 
			this->comboBox1->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(6) {L"add <Desc> start <time> end<time>", 
				L"delete <Desc>", L"undo", L"redo", L"edit <Desc>", L"alternate <keyword> <new keyword>"});
			this->comboBox1->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->comboBox1->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(12, 199);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(380, 21);
			this->comboBox1->TabIndex = 1;
			this->comboBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::comboBox1_KeyDown);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(404, 262);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->dataGridView1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->Text = L"iDo";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void comboBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				  if(e->KeyCode == Keys::Enter)
				 {
					 comboBox1->Items->Clear();
					 System::String^ str1;
					 str1=comboBox1->Text;
					 StreamWriter ^ AppendText();
					 StreamWriter^ sw1 = gcnew StreamWriter("Input.txt",true);
					 sw1->WriteLine(str1);
					 sw1->Close();



					 StreamReader^ din= File::OpenText ("text2.txt");
					 dataGridView1->RowCount=0;
					 int countLines=0;
					 while(din->ReadLine())
						 countLines++;
					 countLines/=3;
					 for(int i=0; i<countLines;i++)
						 dataGridView1->Rows->Add();
					 din->Close();

					 din= File::OpenText ("text2.txt");
					 String^ str;
					 int cellIndex=0;
					 int count=1;
					 for(int i=0;i<countLines;i++)
					 {

						 dataGridView1->Rows[i]->Cells[0]->Value=count.ToString();
						 dataGridView1->Rows[i]->Cells[1]->Value=din->ReadLine();
						 str=din->ReadLine();
						if(str)
							 dataGridView1->Rows[i]->Cells[2]->Value=str;
						 else
							 dataGridView1->Rows[i]->Cells[2]->Value=" ";
						 str=din->ReadLine();
						 if(str)
							dataGridView1->Rows[i]->Cells[3]->Value=str;
						 else
							 dataGridView1->Rows[i]->Cells[3]->Value=" ";

						 int cellIndex=0;
						 count++;

					 }
					 din->Close();
				 
			  }
			/*comboBox1->DroppedDown=true;
			comboBox1->Items->Clear();
			String^ myString;
			myString= "added";
			comboBox1->Items->Add(myString);

			  if(e->KeyCode == Keys::Right)
			  {
				  comboBox1->Focus();


			}*/
			  

			 }
};
}

