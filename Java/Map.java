package Java;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

class Map {
    private Tile[][] tiles;
    public int width;
    public int height;

    private static class Room {
        int x, y, width, height;
    }

    private List<Room> rooms;
    private Random random;

    public Map(int width, int height) {
        this.width = width;
        this.height = height;
        this.tiles = new Tile[height][width];
        this.rooms = new ArrayList<>();
        this.random = new Random();

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                tiles[y][x] = new Tile(TileType.WALL);
            }
        }
    }

    public void setTile(int x, int y, TileType type) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            tiles[y][x] = new Tile(type);
        }
    }

    public void setTile(int x, int y, Tile newTile) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            tiles[y][x] = newTile;
        }
    }

    public Tile getTile(int x, int y) {
        return tiles[y][x];
    }

    public void displayMap() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                char symbol = ' ';
                Tile currentTile = tiles[y][x];
                switch (currentTile.getType()) {
                    case WALL: symbol = ' '; break;
                    case FLOOR: symbol = '.'; break;
                    case DOOR: symbol = '+'; break;
                    default: break;
                }

                if (currentTile.hasEntity()) {
                    symbol = currentTile.getEntity().getChar();
                }

                System.out.print(symbol);
            }
            System.out.println();
        }
    }

    private void createCorridor(int x1, int y1, int x2, int y2) {
        if (x1 > x2) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        if (y1 > y2) {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }

        for (int x = x1; x <= x2; x++) {
            tiles[y1][x].setType(TileType.FLOOR);
           //setTile(x, y1, TileType.FLOOR);
        }

        for (int y = y1; y <= y2; y++) {
            tiles[y][x2].setType(TileType.FLOOR);
            //setTile(x2, y, TileType.FLOOR);
        }
    }

    public boolean generateDungeonLevel(int maxFeatures) {
        int roomWidth = 5 + random.nextInt(6);
        int roomHeight = 5 + random.nextInt(6);
        int roomX = (width - roomWidth) / 2;
        int roomY = (height - roomHeight) / 2;

        Room initialRoom = new Room();
        initialRoom.x = roomX;
        initialRoom.y = roomY;
        initialRoom.width = roomWidth;
        initialRoom.height = roomHeight;
        rooms.add(initialRoom);

        for (int y = roomY; y < roomY + roomHeight; y++) {
            for (int x = roomX; x < roomX + roomWidth; x++) {
                tiles[y][x].setType(TileType.FLOOR);
            }
        }

        for (int i = 0; i < maxFeatures; i++) {
            Room room = rooms.get(random.nextInt(rooms.size()));
            int wall = random.nextInt(4);

            Room newRoom = new Room();
            switch (wall) {
                case 0: // Upper wall
                    newRoom.x = room.x + random.nextInt(room.width);
                    newRoom.y = room.y - (2 + random.nextInt(3));
                    newRoom.width = 3 + random.nextInt(4);
                    newRoom.height = 2 + random.nextInt(3);
                    break;
                case 1: // Lower wall
                    newRoom.x = room.x + random.nextInt(room.width);
                    newRoom.y = room.y + room.height + (1 + random.nextInt(3));
                    newRoom.width = 3 + random.nextInt(4);
                    newRoom.height = 2 + random.nextInt(3);
                    break;
                case 2: // Left wall
                    newRoom.x = room.x - (2 + random.nextInt(3));
                    newRoom.y = room.y + random.nextInt(room.height);
                    newRoom.width = 2 + random.nextInt(3);
                    newRoom.height = 3 + random.nextInt(4);
                    break;
                case 3: // Right wall
                    newRoom.x = room.x + room.width + (1 + random.nextInt(3));
                    newRoom.y = room.y + random.nextInt(room.height);
                    newRoom.width = 2 + random.nextInt(3);
                    newRoom.height = 3 + random.nextInt(4);
                    break;
            }

            // Check if the new room can be added
            boolean canAdd = true;
            for (Room r : rooms) {
                if (newRoom.x < 0 || newRoom.y < 0 || newRoom.x + newRoom.width > width || newRoom.y + newRoom.height > height
                        || !(newRoom.x + newRoom.width <= r.x || newRoom.x >= r.x + r.width ||
                        newRoom.y + newRoom.height <= r.y || newRoom.y >= r.y + r.height)) {
                    canAdd = false;
                    break;
                }
            }

            if (canAdd) {
                int centerX1 = room.x + room.width / 2;
                int centerY1 = room.y + room.height / 2;
                int centerX2 = newRoom.x + newRoom.width / 2;
                int centerY2 = newRoom.y + newRoom.height / 2;

                createCorridor(centerX1, centerY1, centerX2, centerY2);

                rooms.add(newRoom);
                for (int y = newRoom.y; y < newRoom.y + newRoom.height; y++) {
                    for (int x = newRoom.x; x < newRoom.x + newRoom.width; x++) {
                        tiles[y][x] = new Tile(TileType.FLOOR);
                    }
                }
            }
        }

        return true; // Successful completion of level generation
    }
}
