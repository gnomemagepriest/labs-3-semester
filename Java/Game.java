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
    private Random rand;

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

        int targetX = player.getPosition()[0] + dx;
        int targetY = player.getPosition()[1] + dy;

        if (map.getTile(targetX, targetY).hasEntity()) {
            for (Enemy enemy : enemies) {
                if (enemy.getPosition()[0] == targetX && enemy.getPosition()[1] == targetY) {
                    int prevHealth = enemy.getHealth();
                    attackEnemy(player, enemy);
                    int newHealth = enemy.getHealth();

                    logger.addLine("You dealt " + (prevHealth - newHealth) 
                        + " damage to " + enemy.getName() 
                        + " (" + newHealth + " left)");

                    if (newHealth <= 0) {
                        logger.addLine(enemy.getName() + " is dead now");
                        for (Item item : enemy.inventory.getItems()) {
                            map.getTile(targetX, targetY).addItem(item);
                        }
                        map.getTile(targetX, targetY).deleteEntity();
                        enemies.remove(enemy);
                    }
                    break;
                }
            }
        } else {
            moveEntity(player, dx, dy);
        }
    }

    private void attackEnemy(Player player, Enemy enemy) {
        int damage = player.attack;
        enemy.takeDamage(damage);
        if (enemy.getHealth() <= 0) {
            player.gainXP(enemy.getXPValue());
            enemy.health = 0;
        }
    }

    private void moveEntity(Entity entity, int dx, int dy) {
        int[] position = entity.getPosition();
        int newX = position[0] + dx;
        int newY = position[1] + dy;

        if (newX >= 0 && newY >= 0 && newX < map.getWidth() && newY < map.getHeight()) {
            Tile newTile = map.getTile(newX, newY);

            if (newTile.isWalkable() && !newTile.hasEntity()) {
                if (newTile.hasItems()) {
                    for (Item item : newTile.getItems()) {
                        entity.inventory.addItem(item);
                        logger.addLine(entity.getName() + " has picked up " + item.getName());
                    }
                    newTile.deleteItems();
                }
                map.getTile(position[0], position[1]).deleteEntity();
                newTile.placeEntity(entity);
                entity.setPosition(newX, newY);
            }
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

        int totalEntities = enemies.size() + 1 + 6; // +1 для игрока + 6 для предметов
            if (freeTiles.size() < totalEntities) {
                throw new RuntimeException("Недостаточно свободных клеток для размещения всех врагов и игрока.");
        }

        int i = 0;
        for (Enemy enemy : enemies) {
            enemy.setPosition(freeTiles.get(i)[0], freeTiles.get(i)[1]);
            map.getTile(freeTiles.get(i)[0], freeTiles.get(i)[1]).placeEntity(enemy);
            i++;
        }

        List<Item> itemsToPlace = List.of(
            new Item("Book of Enlightenment"),
            new Item("Shield"),
            new Weapon("Dagger", 2),
            new Weapon("Sword", 5),
            new Potion("Murky", "Flame"),
            new Potion("Yellow", "Levitation")
        );

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
                    player.inventory.sortItems();
                    System.out.println(player.inventory.getDescription());
                    try {
                        System.in.read();
                    } catch (IOException e) {
                        System.out.println(e);
                    }
                    break;
                case 't':
                    player.inventory.sortItems();
                    System.out.println("What item to drop?: ");
                    Scanner scanner = new Scanner(System.in);
                    String itemName = scanner.next();
                    var item = player.inventory.popItem(itemName);
                    if (item != null) {
                        map.getTile(player.getPosition()[0], player.getPosition()[1]).addItem(item);
                        logger.addLine("You dropped " + itemName);
                    }
                    else {
                        logger.addLine("No such item in your inventory.");
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
                // Случайное перемещение врагов
                moveEntity(enemy, rand.nextInt(3) - 1, rand.nextInt(3) - 1);
            }
        }
    }

    private void getDebugValues() {
        getInput();
        switch (input) {
            case '1':
                System.out.println("Created entities: " + Entity.getTotalEntities());
                break;
            case '2':
                System.out.println("Player health before takeDamage: " + player.getHealth());
                player.takeDamage(10).takeDamage(10);
                System.out.println("Player health after takeDamage: " + player.getHealth());
                break;
            case '3':
                System.out.println(player);
                if (!enemies.isEmpty()) {
                    System.out.println(enemies.get(0));
                }
                break;
            case '4':
                try {
                    cloneTest();
                }
                catch (CloneNotSupportedException e) {
                    e.printStackTrace();
                }
        }

        try {
            System.in.read();
        } catch (IOException e) {
            // Обработка исключения
        }
    }

    private void cloneTest() throws CloneNotSupportedException {
        Item original = new Item("Glass of water");

        System.out.println("\nOriginal item: " + original);
        Item shallow = (Item) original.clone();
        System.out.println("\nShallow clone: " + shallow);

        original.addTag("made of glass");
        System.out.println("\n\nAded tag: " + original);
        System.out.println("\nShallow clone:" + shallow);

        Item deep = original.deepClone();
        System.out.println("\n\nDeep clone: " + deep);

        original.addTag("drinkable");
        System.out.println("\nAdded tag: " + original);
        System.out.println("\nDeep clone: " + deep);
    }
}
