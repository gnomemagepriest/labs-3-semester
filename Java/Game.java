package Java;

import java.io.IOException;
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
        placeFeatures();
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
        int[] position = entity.getPosition();
        int newX = position[0] + dx;
        int newY = position[1] + dy;

        if (!(newX >= 0 && newY >= 0 && newX < map.getWidth() && newY < map.getHeight())) {
            return;
        }

        Tile newTile = map.getTile(newX, newY);

        if (newTile.isWalkable() && !newTile.hasEntity()) {
            if (newTile.hasItems()) {
                for (Item item : newTile.getItems()) {
                    entity.addItem(item);
                    logger.addLine(entity.getName() + " has picked up " + item.getName());
                }
                newTile.deleteItems();
            }
            map.getTile(position[0], position[1]).deleteEntity();
            newTile.placeEntity(entity);
            entity.setPosition(newX, newY);
        }
    }

    private void getInput() {
        Scanner scanner = new Scanner(System.in);
        input = scanner.next().charAt(0);
    }

    public void placeFeatures() {
        for (int k = 0; k < 10; k++) {
            enemies.add(new Enemy());
        }

        List<int[]> freeTiles = new ArrayList<>();

        for (int y = 0; y < map.getHeight(); y++) {
            for (int x = 0; x < map.getWidth(); x++) {
                Tile tile = map.getTile(x, y);
                if (!tile.hasEntity() && tile.isWalkable()) {
                    freeTiles.add(new int[]{x, y});
                }
            }
        }

        java.util.Collections.shuffle(freeTiles);

        int totalEntities = enemies.size() + 1 + 3;
        if (freeTiles.size() < totalEntities) {
            throw new RuntimeException("Недостаточно свободных клеток для размещения всех врагов и игрока.");
        }

        int i = 0;
        for (Enemy enemy : enemies) {
            enemy.setPosition(freeTiles.get(i)[0], freeTiles.get(i)[1]);
            map.getTile(freeTiles.get(i)[0], freeTiles.get(i)[1]).placeEntity(enemy);
            i++;
        }

        List<Item> itemsToPlace = List.of(new Item("Dagger"), new Item("Potion"), new Item("Shield"));
        for (Item item : itemsToPlace) {
            map.getTile(freeTiles.get(i)[0], freeTiles.get(i)[1]).addItem(item);
            i++;
        }

        player.setPosition(freeTiles.get(i)[0], freeTiles.get(i)[1]);
        map.getTile(freeTiles.get(i)[0], freeTiles.get(i)[1]).placeEntity(player);
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
                case 'i':
                    try {
                        System.out.println(player.getInventoryDescription());
                        System.in.read();
                    } catch (IOException e) {
                        System.out.println(e);
                    }
                    
                    break;
                case '~':
                    System.out.println("DEBUG MODE");
                    getDebugValues();
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

    private void getDebugValues() {
        getInput();
        switch (input)
        {
        case '1':
            System.out.println("Created entities: " + Entity.getTotalEntities());
            break;
        case '2':
            System.out.println("Player health before takeDamage: " + player.getHealth());
            player.takeDamage(10).takeDamage(6);
            System.out.println("Player health after takeDamage: " + player.getHealth());
            break;
        }

        try {
            System.in.read();
        } catch (IOException e) {
            //
        }
    }
}
