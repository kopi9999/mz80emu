#include "MemoryModule.hpp"
#include <wx/sizer.h>
#include <ctime> 
#include <sstream>
#include <iomanip>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* instanceSizer = new wxBoxSizer(wxHORIZONTAL);
    instanceList = new wxListBox(panel, wxID_ANY);

    TableTextValues();

    GridCreate();


    panel->SetSizer(mainSizer);
    
}


void MainFrame::GridCreate()
{
    const int numRows = 14;
    const int numCols = 17;

    grid = new wxGrid( this,    
        -1,
        wxPoint( 0, 0 ),
        wxSize( 700, 300 ) );
    grid->CreateGrid(numCols, numRows);
    int selectedTableRecord = 0 ;
    unsigned char byteVal = 0x20;
    for(int i = 0 ; i < numRows; i++)
    {
        for(int j = 0; j < numCols-1; j++)
        {
            std::stringstream ss;
                ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)byteVal;
                grid->SetCellValue(i, j, ss.str());
                byteVal++;
            selectedTableRecord++;
        }
    }

    for (int row = 0; row < numRows; ++row) {
            wxString asciiStr;
            for (int col = 0; col < 16; ++col) {
                wxString hexVal = grid->GetCellValue(row, col);
                long byte;
                if (hexVal.ToLong(&byte, 16)) {
                    char ch = static_cast<char>(byte);
                    asciiStr += wxString::Format("%c", std::isprint(ch) ? ch : '.');
                } else {
                    asciiStr += '.';
                }
            }
            grid->SetCellValue(row, 16, asciiStr);
        }
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
        memory_table[i] = static_cast<u_int8_t>(std::rand() % 256); // Random byte (0-255)
    }
}