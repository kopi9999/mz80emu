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
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),refresherTimer(this)
{   
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* instanceSizer = new wxBoxSizer(wxHORIZONTAL);
    instanceList = new wxListBox(panel, wxID_ANY);

    GridCreate(panel);
    //making the grid scalable with size of the window?? i think???
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
    //the refresh on change in one row
    grid->Bind(wxEVT_GRID_CELL_CHANGED, &MainFrame::OnChangeRow, this);
    

    panel->SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);


    //the refresh code
    Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
    refresherTimer.Start(40000);
    startTime = wxGetLocalTimeMillis();
};

//creates and fills grid with random data
void MainFrame::GridCreate(wxPanel* panel)
{
    const int numRows = 20;
    const int numCols = 11;
    grid = new wxGrid( panel,    
        -1,
        wxPoint( 0, 0 ),
        wxSize( 800, 600 ) );
    grid->CreateGrid(numRows, numCols);
    GridFill(numRows , numCols);
    //for(int c = 0; c < numRows; c++){
    //    grid->SetLabel(c , c*10);
    //}

}

//generates values for the grid
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

//le refresher of grid on change
void MainFrame::Refresher()
{
    int numRow = 20;
    int numCol = 11;
    GridFill(numRow , numCol);
    grid->ForceRefresh();
}

//timer
void MainFrame::OnTimer(wxTimerEvent& event)
{
    wxLongLong now = wxGetLocalTimeMillis();
    Refresher();
}

//the on change event that is activatet when vale is entered throu grind and affect the grid itslef but not yet the value table wip
void MainFrame::OnChangeRow(wxGridEvent& event)
{
    int selectedRow = event.GetRow();
    int selectedCol = event.GetCol();
    int numCol = 11;
 
    //if the cell i normal and not asci
    if (selectedCol != 11){
    wxString asciiStr;
    for (int col = 0; col < numCol-1; ++col) {
        wxString hexVal = grid->GetCellValue(selectedRow, col);
        long byte;
        if (hexVal.ToLong(&byte, numCol-1)) {
            char ch = static_cast<char>(byte);
            asciiStr += wxString::Format("%c", std::isprint(ch) ? ch : '.');
        } 
        else 
        {
            asciiStr += '.';
        }
    }
    grid->SetCellValue(selectedRow, numCol-1, asciiStr);
    }
    //whan changes cell is the ASCI one 
    else 
    {
        wxString hexVal = grid->GetCellValue(selectedRow , selectedCol);
        //code that combines the input and the saved data
        grid->SetCellValue(selectedRow , selectedCol , hexVal);
        wxString asciiStr;
        char hexValTable = wxSplit(hexVal);
        for (int col = 0; col < 10; ++col) {
            long byte;

            if (hexValTable[col] != ".")
            {
                long cha = static_cast<long>(hexValTable[col]);
                
            }

            if (hexVal.ToLong(&byte, numCol-1)) {
                char ch = static_cast<char>(byte);
                asciiStr += wxString::Format("%c", std::isprint(ch) ? ch : '.');
            } 
            else 
            {
                asciiStr += '.';
            }
            grid->SetCellValue(selectedRow , col , asciiStr);
        }
    }
    grid->ForceRefresh();
}

//fils grid with data given by te table
void MainFrame::GridFill(int Rows , int Cols)
{
    TableTextValues();
    int selectedTableRecord = 0 ;
    unsigned char byteVal = 0x20;
    for(int i = 0 ; i < Rows; i++)
    {
        for(int j = 0; j < Cols-1; j++)
        {
            std::stringstream ss;
                //ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)byteVal;
                ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)memory_table[(int)byteVal];
                grid->SetCellValue(i, j, ss.str());

                
                byteVal++;
            selectedTableRecord++;
        }
    }

    for (int row = 0; row < Rows; ++row) {
            wxString asciiStr;
            for (int col = 0; col < Cols-1; ++col) {
                wxString hexVal = grid->GetCellValue(row, col);
                long byte;
                if (hexVal.ToLong(&byte, Cols-1)) {
                    char ch = static_cast<char>(byte);
                    asciiStr += wxString::Format("%c", std::isprint(ch) ? ch : '.');
                } else {
                    asciiStr += '.';
                }
            }
            grid->SetCellValue(row, Cols-1, asciiStr);
        }
}

//WIP the right click menu that allowns to change the refresh rate
void MainFrame::OnRightClick(wxGridEvent& event)
{
    wxMenu menu;

    menu.Append(1001, "Opcja 1");
    menu.Append(1002, "Opcja 2");

    // pokaż menu w miejscu kliknięcia
    PopupMenu(&menu, event.GetPosition());
}

//Make that if space bar is hit the refreshment stops and the value can be changed manualy 
//Upon hiting enter the row ASCI form shoud refresh to acomodite change 
//or alterativli on every change ASCI form shoud responce with value change 
//

// when 11 col is in edit mode clean it and start a new window / other form to eddit memory
//when edited the value is set by delfy tu zero and the entered value is apped in the forn to zthe value