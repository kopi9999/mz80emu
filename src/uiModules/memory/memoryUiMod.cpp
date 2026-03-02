#include "memoryUiMod.hpp"
#include <ctime> 
#include <sstream>
#include <iomanip>
#include <stdio.h>

using namespace std;

const char* moduleName = "memory";
const char* moduleDescription = "UI module for displaying memory content";
const uint16_t moduleMajorVersion = 1;
const uint16_t moduleMinorVersion = 1;
const uint16_t protocolVersion = 1;

UiModulePanel::UiModulePanel(wxControl* parent, void* instance, void** interfaces) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), 
    instance((struct Instance*) instance),
    interfaces(interfaces),
    refresherTimer(this) {
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer* instanceSizer = new wxBoxSizer(wxHORIZONTAL);
        instanceList = new wxListBox(this, wxID_ANY);

        GridCreate(this);
        // making the grid scalable with size of the window
        mainSizer->Add(grid, 1, wxEXPAND | wxALL, 0);
        grid->SetRowLabelSize(50);
        int lastColWidth = 120;
        grid->SetColSize(10, lastColWidth);
        grid->SetColMinimalWidth(0, 40);
        grid->SetColMinimalAcceptableWidth(20);
        grid->Bind(wxEVT_SIZE, [this](wxSizeEvent& event) {
            int numCols = grid->GetNumberCols();
            int numRows = grid->GetNumberRows();
            int totalWidth = grid->GetClientSize().GetWidth();
            int firstRowWidth = grid->GetRowLabelSize();
            int lastColWidth = grid->GetColSize(numCols-1);
            int colWidth = (totalWidth-firstRowWidth-lastColWidth) / (numCols-1); 
            for (int c = 0; c < numCols-1; ++c) {
                grid->SetColSize(c, colWidth);
                grid->SetColLabelValue(c, to_string(c));
            }
            for (int d=0; d<numRows ; ++d){
                grid->SetRowLabelValue(d, to_string(d));
            }
            grid->SetColLabelValue(numCols-1, "ASCII");
            event.Skip();
        });
        // the refresh on change in one row
        grid->Bind(wxEVT_GRID_CELL_CHANGED, &UiModulePanel::OnChangeRow, this);

        grid->Bind(wxEVT_CONTEXT_MENU, &UiModulePanel::OnGridContextMenu, this);
        Bind(wxEVT_MENU, &UiModulePanel::OnRefreshMenu, this, ID_MENU_REFRESH);

        this->SetSizer(mainSizer);
        mainSizer->SetSizeHints(this);

        grid->DisableDragColSize();
        grid->DisableDragRowSize();

        // the refresh code
        Bind(wxEVT_TIMER, &UiModulePanel::OnTimer, this);
        refresherTimer.Start(250);
    }

// creates and fills grid with initial data
void UiModulePanel::GridCreate(wxPanel* panel)
{
    const int numRows = GRID_HEIGHT;
    const int numCols = 11;
    grid = new wxGrid(
        panel,
        -1,
        wxPoint( 0, 0 ),
        wxSize( 800, 600 )
    );
    grid->CreateGrid(numRows, numCols);
    GridFill(numRows, numCols);
}

void UiModulePanel::OnGridContextMenu(wxContextMenuEvent& event)
{
    wxMenu menu;
    menu.Append(ID_MENU_REFRESH, "Refresh");

    // Position correctly at mouse
    wxPoint pos = event.GetPosition();
    if (pos == wxDefaultPosition) {
        pos = wxGetMousePosition();
    }

    pos = grid->ScreenToClient(pos);
    grid->PopupMenu(&menu, pos);
}

void UiModulePanel::OnRefreshMenu(wxCommandEvent&)
{
    Refresher();
}

// le refresher of grid on change
void UiModulePanel::Refresher()
{
    int numRow = GRID_HEIGHT;
    int numCol = 11;
    GridFill(numRow , numCol);
    grid->ForceRefresh();
}

// timer
void UiModulePanel::OnTimer(wxTimerEvent& event)
{
    wxLongLong now = wxGetLocalTimeMillis();
    Refresher();
}

// on change event that is activated when value is entered through grid and affect the grid itself and the value table
void UiModulePanel::OnChangeRow(wxGridEvent& event)
{
    int selectedRow = event.GetRow();
    int selectedCol = event.GetCol();
    int numCol = 11;
 
    // if the cell is normal and not ascii
    if (selectedCol != 10){
    wxString asciiStr;
    wxString hexVal;
    for (int col = 0; col < numCol-1; ++col) {
        
        hexVal = grid->GetCellValue(selectedRow, col);
        
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

    uint32_t value = 0;
    hexVal = grid->GetCellValue(selectedRow, selectedCol);
    hexVal.ToUInt(&value, 16);
    instance->data[selectedRow * 10 + selectedCol] = value;
    }
    // when changed cell is the ASCII one 
    else 
    {
        wxString hexVal = grid->GetCellValue(selectedRow , selectedCol);
        // code that combines the input and the saved data
        wxString asciiStr;
        size_t base = 10 * static_cast<size_t>(selectedRow);
        for (int col = 0; col < 10; ++col) {
            
            if (hexVal.length() > col && hexVal[col] != '.')
            {
                uint8_t val = static_cast<uint8_t>(hexVal[col]);
                instance->data[base + col] = val;
            }

        }
        int selectedTableRecord = 0;
        unsigned char byteVal = 10 * selectedRow;
        for(int j = 0; j < numCol-1; ++j)
        {
                std::stringstream stringstream;
                unsigned int val = static_cast<unsigned char>(instance->data[byteVal]);
                stringstream << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << val;
                grid->SetCellValue(selectedRow, j, stringstream.str());

                byteVal++;
                selectedTableRecord++;
        }
    }
    grid->ForceRefresh();
}

// fills grid with data given by the table
void UiModulePanel::GridFill(int Rows , int Cols)
{
    int selectedTableRecord = 0;
    unsigned char byteVal = 0x20;
    for(int i = 0; i < Rows; ++i)
    {
        for(int j = 0; j < Cols-1; ++j)
        {
            uint8_t byte = instance->data[selectedTableRecord];
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
            uint8_t byte = instance->data[selectedTableRecord]; // read raw byte

            char ch = static_cast<char>(byte);

            // show printable ASCII, otherwise show '.'
            asciiStr += wxString::Format("%c", std::isprint(static_cast<unsigned char>(ch)) ? ch : '.');
        }
        grid->SetCellValue(row, Cols-1, asciiStr);
    }
}

// WIP the right click menu that allows to change the refresh rate
void UiModulePanel::OnRightClick(wxGridEvent& event)
{
    wxMenu menu;

    menu.Append(1001, "Opcja 1");
    menu.Append(1002, "Opcja 2");

    // show menu at click position
    PopupMenu(&menu, event.GetPosition());
}

wxPanel* getPanel(wxControl* parent, void* instance, void** interfaces)
{
    return new UiModulePanel(parent, instance, interfaces);
}

//Make that if space bar is hit the refreshment stops and the value can be changed manualy
//Upon hiting enter the row ASCI form shoud refresh to acomodite change
//or alterativli on every change ASCI form shoud responce with value change

// when 11 col is in edit mode clean it and start a new window / other form to eddit memory
//when edited the value is set by delfy tu zero and the entered value is apped in the forn to zthe value

//add saving to memory when changing single cell


//reads from selected file
bool UiModulePanel::ReadFromSelectedBINFile(const wxString& filePath)
{
    int ReadFile = 0;
    //here have a file readerin BIN file to a some zmienna a nie trzeb gdzieś zroić 
    //guzik zeby odpalało takie menu do wyboru pliku co jest osobną funkcja w wxwidget 
    //i fukcja zapisze czy cos ok ok :3

    wxFile file;
    if (!file.Open(filePath, wxFile::read))
    {
        wxLogError("Couldnt open the file");
        return false;
    }

    wxFileOffset fileSize = file.Length();

    size_t elementCount = fileSize / sizeof(instance->data);


    if (file.Read(instance->data, fileSize) != fileSize)
    {
        wxLogError("Error while reading the file");
        return false;
    }

    file.Close();
    return true;

}

//opens a selcet file window
void UiModulePanel::SelectFileWindow(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(
        this,
        "Open BIN File",
        "",
        "",
        "Pliki BIN (*.bin)|*.bin",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    if (ReadFromSelectedBINFile(openFileDialog.GetPath()))
    {
        wxLogMessage("Loaded %zu elements", sizeof(instance->data));
    }
}