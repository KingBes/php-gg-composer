struct string
{
    unsigned char *str;
    int len;
    int is_lit;
};
typedef struct string string;

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};
typedef struct Color Color;

typedef enum
{
    ArrayFlags__noslices = 1U, // u64(1) << 0
    ArrayFlags__noshrink = 2U, // u64(1) << 1
    ArrayFlags__nogrow = 4U,   // u64(1) << 2
    ArrayFlags__nofree = 8U,   // u64(1) << 3
} ArrayFlags;

struct array
{
    void *data;
    int offset;
    int len;
    int cap;
    ArrayFlags flags;
    int element_size;
};
typedef struct array array;

typedef struct Config
{
    int width;
    int height;
    bool retina;
    bool resizable;
    void *user_data;
    int font_size;
    bool create_window;
    string window_title;
    string html5_canvas_name;
    bool borderless_window;
    bool always_on_top;
    Color bg_color;
    void *init_fn;
    void *frame_fn;
    void *native_frame_fn;
    void *cleanup_fn;
    void *fail_fn;
    void *event_fn;
    void *on_event;
    void *quit_fn;
    void *keydown_fn;
    void *keyup_fn;
    void *char_fn;
    void *move_fn;
    void *click_fn;
    void *unclick_fn;
    void *leave_fn;
    void *enter_fn;
    void *resized_fn;
    void *scroll_fn;
    bool fullscreen;
    float scale;
    int sample_count;
    int swap_interval;
    string font_path;
    string custom_bold_font_path;
    bool ui_mode;
    array font_bytes_normal;
    array font_bytes_bold;
    array font_bytes_mono;
    array font_bytes_italic;
    bool native_rendering;
    bool enable_dragndrop;
    int max_dropped_files;
    int max_dropped_file_path_length;
    int min_width;
    int min_height;
};
typedef struct Config Config;

typedef struct gg__PipelineContainer
{
    void *alpha;
    void *add;
};
typedef struct gg__PipelineContainer gg__PipelineContainer;

struct DenseArray
{
    int key_bytes;
    int value_bytes;
    int cap;
    int len;
    unsigned int deletes;
    unsigned char *all_deleted;
    unsigned char *keys;
    unsigned char *values;
};
typedef struct DenseArray DenseArray;

struct map
{
    int key_bytes;
    int value_bytes;
    unsigned int even_index;
    unsigned char cached_hashbits;
    unsigned char shift;
    DenseArray key_values;
    unsigned int *metas;
    unsigned int extra_metas;
    bool has_string_keys;
    void *hash_fn;
    void *key_eq_fn;
    void *clone_fn;
    void *free_fn;
    int len;
};
typedef struct map map;

struct gg__FT
{
    void *fons;
    int font_normal;
    int font_bold;
    int font_mono;
    int font_italic;
    map fonts_map;
    float scale;
};
typedef struct gg__FT gg__FT;

typedef enum
{
    gg__MouseButtons__left = 1U,   // u64(1) << 0
    gg__MouseButtons__right = 2U,  // u64(1) << 1
    gg__MouseButtons__middle = 4U, // u64(1) << 2
} gg__MouseButtons;

typedef enum
{
    gg__Modifier__shift = 1U, // u64(1) << 0
    gg__Modifier__ctrl = 2U,  // u64(1) << 1
    gg__Modifier__alt = 4U,   // u64(1) << 2
    gg__Modifier__super = 8U, // u64(1) << 3
} gg__Modifier;

typedef enum
{
    gx__VerticalAlign__top = 0,      // FONS_ALIGN_TOP
    gx__VerticalAlign__middle = 1,   // FONS_ALIGN_MIDDLE
    gx__VerticalAlign__bottom = 2,   // FONS_ALIGN_BOTTOM
    gx__VerticalAlign__baseline = 3, // FONS_ALIGN_BASELINE
} gx__VerticalAlign;

typedef enum
{
    gx__HorizontalAlign__left = 0,   // FONS_ALIGN_LEFT
    gx__HorizontalAlign__center = 1, // FONS_ALIGN_CENTER
    gx__HorizontalAlign__right = 2,  // FONS_ALIGN_RIGHT
} gx__HorizontalAlign;

typedef struct gx__TextCfg
{
    Color color;
    int size;
    gx__HorizontalAlign align;
    gx__VerticalAlign vertical_align;
    int max_width;
    string family;
    bool bold;
    bool mono;
    bool italic;
};
typedef struct gx__TextCfg gx__TextCfg;

struct gg__FPSConfig
{
    int x;
    int y;
    int width;
    int height;
    bool show;
    gx__TextCfg text_config;
    Color background_color;
};
typedef struct gg__FPSConfig gg__FPSConfig;

struct Context
{
    bool render_text;
    array image_cache;
    bool needs_refresh;
    int ticks;
    bool native_rendering;
    float scale;
    int width;
    int height;
    void *clear_pass;
    void *window;
    gg__PipelineContainer *pipeline;
    Config config;
    void *user_data;
    gg__FT *ft;
    bool font_inited;
    bool ui_mode;
    unsigned long long frame;
    unsigned char mbtn_mask;
    gg__MouseButtons mouse_buttons;
    int mouse_pos_x;
    int mouse_pos_y;
    int mouse_dx;
    int mouse_dy;
    int scroll_x;
    int scroll_y;
    gg__Modifier key_modifiers;
    bool key_repeat;
    unsigned char *pressed_keys;
    unsigned char *pressed_keys_edge;
    gg__FPSConfig fps;
};
typedef struct Context Context;

Context *new_context(Config configs);

void run(Context *context);