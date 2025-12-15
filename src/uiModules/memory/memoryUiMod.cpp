#include "memoryUiMod.hpp"
#include <ctime> 
#include <sstream>
#include <iomanip>
#include <stdio.h>

const char* moduleName = "memory";
const char* moduleDescription = "UI module for displaying memory content";
const uint16_t moduleMajorVersion = 1;
const uint16_t moduleMinorVersion = 1;
const uint16_t protocolVersion = 1;

UiModulePanel::UiModulePanel(wxControl* parent, void* instance, void** interfaces) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), 
    instance((struct Instance*) instance),
    interfaces(interfaces) {
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer* instanceSizer = new wxBoxSizer(wxHORIZONTAL);
        instanceList = new wxListBox(this, wxID_ANY);

        GridCreate(this);
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
        grid->Bind(wxEVT_GRID_CELL_CHANGED, &UiModulePanel::OnChangeRow, this);

        grid->Bind(wxEVT_CONTEXT_MENU, &UiModulePanel::OnGridContextMenu, this);
        Bind(wxEVT_MENU, &UiModulePanel::OnRefreshMenu, this, ID_MENU_REFRESH);

        this->SetSizer(mainSizer);
        mainSizer->SetSizeHints(this);


        //the refresh code
        Bind(wxEVT_TIMER, &UiModulePanel::OnTimer, this);
        refresherTimer.Start(40000);
        startTime = wxGetLocalTimeMillis();
    }

//creates and fills grid with random data
void UiModulePanel::GridCreate(wxPanel* panel)
{
    const int numRows = 20;
    const int numCols = 11;
    grid = new wxGrid( panel,    
        -1,
        wxPoint( 0, 0 ),
        wxSize( 800, 600 ) );
    grid->CreateGrid(numRows, numCols);
    TableTextValues();
    GridFill(numRows , numCols);
    //for(int c = 0; c < numRows; c++){
    //    grid->SetLabel(c , c*10);
    //}

}

void UiModulePanel::OnGridContextMenu(wxContextMenuEvent& event)
{
    wxMenu menu;
    menu.Append(ID_MENU_REFRESH, "Refresh");

    // Position correctly at mouse
    wxPoint pos = event.GetPosition();
    if (pos == wxDefaultPosition)
        pos = wxGetMousePosition();

    pos = grid->ScreenToClient(pos);
    grid->PopupMenu(&menu, pos);
}

void UiModulePanel::OnRefreshMenu(wxCommandEvent&)
{
    Refresher(); // your already-existing function
}

//generates values for the grid
void UiModulePanel::TableTextValues()
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
void UiModulePanel::Refresher()
{
    int numRow = 20;
    int numCol = 11;
    GridFill(numRow , numCol);
    grid->ForceRefresh();
}

//timer
void UiModulePanel::OnTimer(wxTimerEvent& event)
{
    wxLongLong now = wxGetLocalTimeMillis();
    Refresher();
}

//the on change event that is activatet when vale is entered throu grind and affect the grid itslef but not yet the value table wip
void UiModulePanel::OnChangeRow(wxGridEvent& event)
{
    int selectedRow = event.GetRow();
    int selectedCol = event.GetCol();
    int numCol = 11;
 
    //if the cell i normal and not asci
    if (selectedCol != 10){
    wxString asciiStr;
    for (int col = 0; col < numCol-1; ++col) {
        
        wxString hexVal = grid->GetCellValue(selectedRow, col);
        long byte;
        
        long value = 0;
        if (hexVal.ToLong(&value, 16) && value >= 0 && value <= 255)
        {
            char ch = static_cast<char>(value);
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
        wxString asciiStr;
        size_t base = 10 * static_cast<size_t>(selectedRow);
        for (int col = 0; col < 10; ++col) {
            
            if (hexVal.length() > col && hexVal[col] != '.')
            {
                uint8_t val = static_cast<uint8_t>(hexVal[col]);
                memory_table[base + col] = val;
            }

        }
        int selectedTableRecord = 0 ;
        unsigned char byteVal = 10 * selectedRow ;
        for(int j = 0; j < numCol-1; j++)
        {
                std::stringstream ss;
                    unsigned int val = static_cast<unsigned char>(memory_table[byteVal]);
                //ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)byteVal;
                ss << std::hex << std::uppercase << std::setfill('0') << std::setw(2)<< val;
                grid->SetCellValue(selectedRow, j, ss.str());

                
                    byteVal++;
                selectedTableRecord++;
        }
    }
    grid->ForceRefresh();
}

//fils grid with data given by te table
void UiModulePanel::GridFill(int Rows , int Cols)
{
    int selectedTableRecord = 0 ;
    unsigned char byteVal = 0x20;
    for(int i = 0 ; i < Rows; i++)
    {
        for(int j = 0; j < Cols-1; j++)
        {
            uint8_t byte = memory_table[selectedTableRecord];
            wxString hex = wxString::Format("%02X", byte);
            grid->SetCellValue(i, j, hex);
            byteVal++;
            selectedTableRecord++;
        }
    }
    
    for (int row = 0; row < Rows; ++row) {
            wxString asciiStr;
            for (int col = 0; col < Cols-1; ++col) {
                selectedTableRecord = row*10+col;
                uint8_t byte = memory_table[selectedTableRecord ];  // read raw byte

                char ch = static_cast<char>(byte);

                // show printable ASCII, otherwise show '.'
                asciiStr += wxString::Format("%c",
                    std::isprint(static_cast<unsigned char>(ch)) ? ch : '.');
            }
            grid->SetCellValue(row, Cols-1, asciiStr);
        }
}

//WIP the right click menu that allowns to change the refresh rate
void UiModulePanel::OnRightClick(wxGridEvent& event)
{
    wxMenu menu;

    menu.Append(1001, "Opcja 1");
    menu.Append(1002, "Opcja 2");

    // pokaż menu w miejscu kliknięcia
    PopupMenu(&menu, event.GetPosition());
}


wxPanel* getPanel(wxControl* parent, void* instance, void** interfaces)
{
    return new UiModulePanel(parent, instance, interfaces);
}

//Make that if space bar is hit the refreshment stops and the value can be changed manualy 
//Upon hiting enter the row ASCI form shoud refresh to acomodite change 
//or alterativli on every change ASCI form shoud responce with value change 
//

// when 11 col is in edit mode clean it and start a new window / other form to eddit memory
//when edited the value is set by delfy tu zero and the entered value is apped in the forn to zthe value