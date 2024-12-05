#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <Windows.h>

// Enemy - противник
typedef struct {
    int health;
    int damage;
    int x, y;
} Enemy;

// Player - управляемый игрок
typedef struct {
    int health;
    int damage;
    int score;
    int level;
    int x, y;
} Player;

// Item - предмет
typedef struct {
    int value;
} Item;

// Tile - одна клетка карты
typedef struct {
    int type; // 0 - стена, 1 - пол
    Enemy* enemy; // указатель на врага
    Player* player; // указатель на игрока
    Item* item;
} Tile;

// Game - класс, управляющий игрой
typedef struct {
    Tile** map;
    int map_width;
    int map_height;
    Player* player;
} Game;

void display_map(Game* game) {
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            if (game->map[x][y].type == 0) {
                printf("#");
            }
            else if (game->map[x][y].player) {
                printf("@");
            }
            else if (game->map[x][y].enemy) {
                printf("E");
            }
            else if (game->map[x][y].item) {
                printf("I");
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }
}

void fill_borders(Game* game) {
    for (int x = 0; x < game->map_width; x++) {
        game->map[x][0].type = 0; // верхняя граница
        game->map[x][game->map_height - 1].type = 0; // нижняя граница
    }
    for (int y = 0; y < game->map_height; y++) {
        game->map[0][y].type = 0; // левая граница
        game->map[game->map_width - 1][y].type = 0; // правая граница
    }
}

// Функция инициализации Tile
Tile* create_tile(int type) {
    Tile* tile = (Tile*)malloc(sizeof(Tile));
    tile->type = type;
    tile->item = NULL;
    tile->enemy = NULL;
    tile->player = NULL;
    return tile;
}

// Функция инициализации Enemy
Enemy* create_enemy(int health, int damage) {
    Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
    enemy->health = health;
    enemy->damage = damage;
    return enemy;
}

// Функция инициализации Player
Player create_player(int health, int damage, int score, int level) {
    Player player;
    player.health = health;
    player.damage = damage;
    player.score = score;
    player.level = level;
    return player;
}

// Функция для атаки игрока
void playerAttack(Player* player, Enemy* enemy) {
    enemy->health -= player->damage;
    printf("You dealt %d damage! Enemy has %d HP left\n", player->damage, enemy->health);
}

// Функция инициализации Game
Game* create_game(int map_width, int map_height) {
    Game* game = (Game*)malloc(sizeof(Game));
    game->map = (Tile**)malloc(sizeof(Tile*) * map_width);
    for (int i = 0; i < map_width; i++) {
        game->map[i] = (Tile*)malloc(sizeof(Tile) * map_height);
    }
    game->map_width = map_width;
    game->map_height = map_height;
    for (int y = 0; y < game->map_height; y++)
        for (int x = 0; x < game->map_width; x++) {
            game->map[x][y] = *create_tile(1); // верхняя граница
        }
    game->player = NULL;
    return game;
}

void move_player(Game* game, int dx, int dy) {
    int new_x = game->player->x + dx;
    int new_y = game->player->y + dy;
    // если движение в границах карты и ходить можно
    if (new_x <= 0 || new_x > game->map_width || new_y <= 0
        || new_y > game->map_height
        || game->map[new_x][new_y].type == 0) {
        return;
    }

    // Атака, если на пути противник
    if (game->map[new_x][new_y].enemy != NULL) {
        playerAttack(game->player, game->map[new_x][new_y].enemy);
        if (game->map[new_x][new_y].enemy->health <= 0) {
            game->map[new_x][new_y].enemy = NULL;
            printf("The enemy is defeated!\n");
            game->player->score += 5;
        }
        while (getchar() != '\n');
        return;
    }

    // подобрать предмет, если на пути предмет
    if (game->map[new_x][new_y].item != NULL) {
        game->player->score += game->map[new_x][new_y].item->value;
        game->map[new_x][new_y].item = NULL;
        printf("You gained an item of value!\n");
        while (getchar() != '\n');
    }

    // перемещение игрока
    game->map[game->player->x][game->player->y].player = NULL;
    game->map[new_x][new_y].player = game->player;
    game->player->x = new_x;
    game->player->y = new_y;
}

int main() {
    int running = 1;

    Game* game = create_game(10, 10);
    Enemy* goblin = create_enemy(50, 10);
    Player player = create_player(100, 20, 0, 1);
    Item necklace;
    necklace.value = 10;
    fill_borders(game);

    game->player = &player;

    // Размещаем игрока и врагов на карте
    game->map[5][5].player = &player;
    player.x = 5;
    player.y = 5;
    game->map[2][2].enemy = goblin;
    goblin->x = 2;
    goblin->y = 2;
    game->map[1][1].item = &necklace;

    // Основной игровой цикл
    while (game->player->health > 0 && running) {
        system("cls");
        display_map(game);

        // Обработка ввода игрока
        int dx = 0, dy = 0;
        char input;
        printf("Your turn: ");
        scanf("%c", &input);
        while (getchar() != '\n');
        switch (input) {
        case 'w': dy = -1; break;
        case 's': dy = 1; break;
        case 'a': dx = -1; break;
        case 'd': dx = 1; break;
        case 'q': running = 0; break;
        break;
        }
        move_player(game, dx, dy);
    }

    printf("Game is over!\n");
    printf("Final score: %d\n", player.score);

    // Освобождение динамически выделенной памяти
    for (int i = 0; i < game->map_width; i++) {
        free(game->map[i]);
    }
    free(game->map);
    free(game);
    free(goblin);

    return 0;
}