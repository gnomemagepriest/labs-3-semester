package Java;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Game {
    private Logger logger;
    private Map map;
    private Player player;
    private List<Enemy> enemies;
    private char input;
    private boolean running;
    Random rand;

    public Game() {
        logger = new Logger();
        map = new Map(40, 20);
        player = new Player();
        enemies = new ArrayList<>();
        input = 0;
        running = true;

        rand = new Random();
        map.generateDungeonLevel(30);
        placeEnemies();
    }

    private void playerTurn() {
        int dx = 0, dy = 0;

        switch (input) {
            case 'w':
                dy = -1;
                break;
            case 's':
                dy = 1;
                break;
            case 'a':
                dx = -1;
                break;
            case 'd':
                dx = 1;
                break;
            default:
                break;
        }

        moveEntity(player, dx, dy);
    }

    private void moveEntity(Entity entity, int dx, int dy) {
        int newX = entity.x + dx;
        int newY = entity.y + dy;
        if (newX > 0 && newY > 0 && newX < map.width && newY < map.height
            && map.getTile(newX, newY).isWalkable() && !map.getTile(newX, newY).hasEntity()) {
            map.setTile(entity.x, entity.y, new Tile(TileType.FLOOR));
            map.setTile(newX, newY, new Tile(entity));
            entity.x = newX;
            entity.y = newY;
        }
    }

    private void getInput() {
        Scanner scanner = new Scanner(System.in);
        input = scanner.next().charAt(0);
    }

    private void placeEnemies() {
        for (int k = 0; k < 10; k++) {
            enemies.add(new Enemy());
        }

        List<int[]> freeTiles = new ArrayList<>();

        for (int y = 0; y < map.height; y++) {
            for (int x = 0; x < map.width; x++) {
                if (!map.getTile(x, y).hasEntity() && map.getTile(x, y).isWalkable()) {
                    System.out.println("Free Tile");
                    freeTiles.add(new int[]{x, y});
                }
            }
        }

        System.out.println(freeTiles.isEmpty());

        // Перемешать свободные клетки
        java.util.Collections.shuffle(freeTiles);

        int totalEntities = enemies.size() + 1; // +1 для игрока
        if (freeTiles.size() < totalEntities) {
            System.err.println("Недостаточно свободных клеток для размещения всех врагов и игрока.");
            throw new RuntimeException("Недостаточно клеток");
        }

        int i = 0;
        for (Enemy enemy : enemies) {
            enemy.x = freeTiles.get(i)[0];
            enemy.y = freeTiles.get(i)[1];
            map.setTile(enemy.x, enemy.y, new Tile(enemy));
            System.out.println(enemy.x + " " + enemy.y);
            i++;
        }

        player.x = freeTiles.get(i)[0];
        player.y = freeTiles.get(i)[1];
        map.setTile(player.x, player.y, new Tile(player));
    }

    public void run() {
        while (running && player.isAlive()) {
            System.out.print("\033[H\033[2J");  
            map.displayMap();
            System.out.println(logger.getLastEvents() + "Input: ");

            getInput();
            switch (input) {
                case 'q':
                    running = false;
                    break;
                default:
                    playerTurn();
                    break;
            }

            for (Enemy enemy : enemies) {
                // Random movement for enemies
                moveEntity(enemy, rand.nextInt(3) - 1, rand.nextInt(3) - 1);
            }
        }
    }
}
