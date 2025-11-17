#include "MemoryModule.hpp"
#include <ctime> 
#include <sstream>
#include <iomanip>
#include <stdio.h>

wxIMPLEMENT_APP(App);

bool App::OnInit(){
  MainFrame* mainFrame = new MainFrame("C++ GUI");
  mainFrame->Show();
  return true;
}

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* instanceSizer = new wxBoxSizer(wxHORIZONTAL);
    instanceList = new wxListBox(panel, wxID_ANY);

    TableTextValues();

    GridCreate(panel);

    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 0);
    grid->SetRowLabelSize(40);
    int lastColWidth = 120;
    grid->SetColSize(10, lastColWidth);
    grid->SetColMinimalWidth(0, 40);
    grid->SetColMinimalAcceptableWidth(20);
    grid->Bind(wxEVT_SIZE, [this](wxSizeEvent& event) {
    int numCols = grid->GetNumberCols();
    int totalWidth = grid->GetClientSize().GetWidth();
    int firstRowWidth = grid->GetRowLabelSize();
    int lastColWidth = grid->GetColSize(10);
    int colWidth = (totalWidth-firstRowWidth-lastColWidth) / (numCols-1); 
    for (int c = 0; c < numCols-1; ++c)
        grid->SetColSize(c, colWidth);
    event.Skip();
    });
    

    panel->SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);
};


void MainFrame::GridCreate(wxPanel* panel)
{
    const int numRows = 20;
    const int numCols = 11;

    grid = new wxGrid( panel,    
        -1,
        wxPoint( 0, 0 ),
        wxSize( 800, 600 ) );
    grid->CreateGrid(numRows, numCols);
    int selectedTableRecord = 0 ;
    unsigned char byteVal = 0x20;
    for(int i = 0 ; i < numRows; i++)
    {
        for(int j = 0; j < numCols-1; j++)
        {
            std::stringstream ss;
                //ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)byteVal;
                ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)memory_table[(int)byteVal];
                grid->SetCellValue(i, j, ss.str());

                
                byteVal++;
            selectedTableRecord++;
        }
    }

    for (int row = 0; row < numRows; ++row) {
            wxString asciiStr;
            for (int col = 0; col < numCols-1; ++col) {
                wxString hexVal = grid->GetCellValue(row, col);
                long byte;
                if (hexVal.ToLong(&byte, numCols-1)) {
                    char ch = static_cast<char>(byte);
                    asciiStr += wxString::Format("%c", std::isprint(ch) ? ch : '.');
                } else {
                    asciiStr += '.';
                }
            }
            grid->SetCellValue(row, numCols-1, asciiStr);
        }

    //for(int c = 0; c < numRows; c++){
    //    grid->SetLabel(c , c*10);
    //}

}


void MainFrame::TableTextValues()
{
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
    int size = sizeof(memory_table)/sizeof(memory_table[0]);
    for (size_t i = 0; i < size; ++i) {
        memory_table[i] = static_cast<uint8_t>(std::rand() % 256); // Random byte (0-255)
    }
}

void MainFrame::Refresher()
{
    int numRow = 20;
    int numCol = 11;

    for (int row = 0; row < numRow; ++row) {
            wxString asciiStr;
            for (int col = 0; col < numCol-1; ++col) {
                wxString hexVal = grid->GetCellValue(row, col);
                long byte;
                if (hexVal.ToLong(&byte, numCol-1)) {
                    char ch = static_cast<char>(byte);
                    asciiStr += wxString::Format("%c", std::isprint(ch) ? ch : '.');
                } else {
                    asciiStr += '.';
                }
            }
            grid->SetCellValue(row, numCol-1, asciiStr);
        }
}