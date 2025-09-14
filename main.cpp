#include <iostream>
#include <raylib.h>
#include <vector>
#include <fstream>
class SelGrid{
    public:
        Rectangle rect;
        bool clicked;
        Color color;
        int type;

        void Draw(){
            DrawRectangleRec(rect, color);
        }

};

void SaveWidowToFile(const std::string& filename, std::vector<SelGrid>& widow){
    std::ofstream file(filename);
    for(int i = 0; i < widow.size(); i++){
        SelGrid wid = widow[i];
        file << wid.rect.x<<" "<<
        wid.rect.y<<" "<<
        wid.rect.width<<" "<<
        wid.rect.height<<" "<<
        wid.clicked<<" "<<
        wid.type <<" "<<
        "\n";
    }
    file.close();
};
void LoadWidowFromFile(const std::string& filename, std::vector<SelGrid>& widow) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    widow.clear();
    SelGrid wid;

    while (file >>
        wid.rect.x >>
        wid.rect.y >>
        wid.rect.width >>
        wid.rect.height >>
        wid.clicked >>
        wid.type)
        {
        widow.push_back(wid);
        }

        file.close();
}


int main(void){
    std::vector<SelGrid> widow;
    int rWidth = 800/7;
    int rHeight = 600/5;
    bool legenda = false;
    LoadWidowFromFile("dni.txt", widow);
    for (int i =0; i < widow.size(); i++){
        if (widow[i].type == 0) widow[i].color = WHITE; //nic
        else if(widow[i].type == 1) widow[i].color = GREEN;//obecny
        else if(widow[i].type == 2) widow[i].color = YELLOW;//spóźnienie
        else if(widow[i].type == 3) widow[i].color = RED;//nieobecność
        else if(widow[i].type == 4) widow[i].color = GRAY;//wolne
    }
    InitWindow(800,600,"TBTS - Terrible Back To School");
    int selectObjectIndex = -1;
    while(!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(BLACK);
        if (IsKeyPressed(KEY_L)) legenda = !legenda;

        for (int i = 0; i < widow.size();i++){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(CheckCollisionPointRec(GetMousePosition(), widow[i].rect)){
                selectObjectIndex = i;
                }
            }
            if(selectObjectIndex>-1){
                if(IsKeyPressed(KEY_ONE)) widow[selectObjectIndex].type = 0;
                if(IsKeyPressed(KEY_O)||IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) widow[selectObjectIndex].type = 1;
                if(IsKeyPressed(KEY_S)) widow[selectObjectIndex].type = 2;
                if(IsKeyPressed(KEY_N)) widow[selectObjectIndex].type = 3;
                if(IsKeyPressed(KEY_W)) widow[selectObjectIndex].type = 4;

            }
        }

        if (IsKeyDown(KEY_LEFT_CONTROL)&&IsKeyPressed(KEY_TAB)){
            SaveWidowToFile("dni.txt", widow);
            std::cout << "Zapisano do pliku"<<std::endl;
        }

        for (auto &wid :widow){
            if (wid.type == 0) wid.color = (CheckCollisionPointRec(mouse, wid.rect))? PINK:WHITE; //nic
            else if(wid.type == 1) wid.color = (CheckCollisionPointRec(mouse, wid.rect))? PINK:GREEN;//obecny
            else if(wid.type == 2) wid.color = (CheckCollisionPointRec(mouse, wid.rect))? PINK:YELLOW;//spóźnienie
            else if(wid.type == 3) wid.color = (CheckCollisionPointRec(mouse, wid.rect))? PINK:RED;//nieobecność
            else if(wid.type == 4) wid.color =(CheckCollisionPointRec(mouse, wid.rect))? PINK: GRAY;//wolne
            wid.Draw();
        }

        for (int i = 0; i < widow.size();i++){
            DrawText(TextFormat("%d",i+1), widow[i].rect.x, widow[i].rect.y, 40, BLACK);
            if (widow[i].type == 1)DrawText("O", (widow[i].rect.x + (widow[i].rect.width)/2)-5, widow[i].rect.y + (widow[i].rect.height)/2, 20, BLACK);
            if (widow[i].type == 2)DrawText("S", (widow[i].rect.x + (widow[i].rect.width)/2)-5, widow[i].rect.y + (widow[i].rect.height)/2, 20, BLACK);
            if (widow[i].type == 3)DrawText("N", (widow[i].rect.x + (widow[i].rect.width)/2)-5, widow[i].rect.y + (widow[i].rect.height)/2, 20, BLACK);
            if (widow[i].type == 4)DrawText("W", (widow[i].rect.x + (widow[i].rect.width)/2)-5, widow[i].rect.y + (widow[i].rect.height)/2, 20, BLACK);
        }

        if(selectObjectIndex>-1)DrawRectangleLines(widow[selectObjectIndex].rect.x, widow[selectObjectIndex].rect.y, widow[selectObjectIndex].rect.width, widow[selectObjectIndex].rect.height, BLACK);
        if(legenda){
            DrawText("Key One to nothing", 5, 0, 20, BLACK);
            DrawText("Key O or RightMouse to present", 5, 15, 20, BLACK);
            DrawText("Key S to late", 5, 30, 20, BLACK);
            DrawText("Key N to absent", 5, 45, 20, BLACK);
            DrawText("Key W to off school", 5, 60, 20, BLACK);
            DrawText("CTRL+TAB to save", 5, 75, 20, BLACK);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
