const int HBLANK_CLOCKS = 204;          // Mode 0
const int VBLANK_CLOCKS = 4560;         // Mode 1
const int OAM_CLOCKS = 80;              // Mode 2
const int DATA_TRANSFER_CLOCKS = 172;   // Mode 3

const int VBLANK_SCANLINE_CLOCKS = VBLANK_CLOCKS / 10;

const int LCD_WIDTH = 160;
const int LCD_HEIGHT = 144;

const int MAP_SIZE = 256;
const int TILES_PER_LINE = 32;


typedef enum SpriteSize {
    SPRITEx8,
    SPRITEx16
} SpriteSize_t;


typedef enum TileDataTableSelect {
    TILE_DATA_UNSIGNED = 0x8000,
    TILE_DATA_SIGNED = 0x8800
} TileDataTableSelect_t;


typedef enum TileMapTableSelect {
    TILE_MAP_1 = 0x9800,
    TILE_MAP_2 = 0x9C00
} TileMapTableSelect_t;


typedef enum VideoMode {
    HBLANK_Mode = 0x00,
    VBLANK_Mode = 0x01,
    OAM_Mode = 0x02,
    Data_Transfer_Mode = 0x03
} VideoMode_t;


typedef enum Colour {
    WHITE = 0x0,
    LIGHT_GRAY = 0x1,
    DARK_GRAY = 0x2,
    BLACK = 0x3
} Colour_t;


typedef enum PixelColour {
    Colour0,
    Colour1,
    Colour2,
    Colour3
} PixelColour_t;


struct Palette {
    Colour_t colour0;
    Colour_t colour1;
    Colour_t colour2;
    Colour_t colour3;
};