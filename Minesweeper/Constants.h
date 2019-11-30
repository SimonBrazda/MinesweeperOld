#pragma once

#define GREY al_map_rgb_f(0.8, 0.8, 0.8)
#define RED al_map_rgb_f(1, 0, 0)
#define BLACK al_map_rgb_f(0, 0, 0)

inline const char* buttText1{ "Begginer" };
inline const char* buttText2{ "Intermediate" };
inline const char* buttText3{ "Expert" };
inline const char* buttText4{ "Custom" };

inline const char* label1{ "Width" };
inline const char* label2{ "Height" };
inline const char* label3{ "Mines" };

inline const int begginer_field_width{ 9 };
inline const int begginer_field_height{ 9 };
inline const int begginer_mines_count{ 10 };

inline const int intermediate_field_width{ 16 };
inline const int intermediate_field_height{ 16 };
inline const int intermediate_mines_count{ 40 };

inline const int expert_field_width{ 30 };
inline const int expert_field_height{ 16 };
inline const int expert_mines_count{ 99 };

inline const int window_width{ 1024 }, window_height{ 768 };
inline const int element_size{ 16 };

inline const int butt_text_x_offset{ 8 };

struct Position {
	int x{};
	int y{};
};

struct Size
{
	int width{ 150 };
	int height{ 50 };
};