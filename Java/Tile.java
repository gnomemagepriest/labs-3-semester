package Java;

import java.util.ArrayList;
import java.util.List;

enum TileType {
    WALL,
    FLOOR,
    DOOR
}

class Tile {
    private TileType type;
    private Entity entity;
    private List<Item> items;

    public Tile(TileType typeOfTile) {
        this.type = typeOfTile;
        this.entity = null;
        this.items = new ArrayList<>();
    }

    public Tile(Entity entityOnTile) {
        this.type = TileType.FLOOR;
        this.entity = entityOnTile;
        this.items = new ArrayList<>();
    }

    public void addItem(Item newItem) {
        items.add(newItem);
    }

    public TileType getType() {
        return type;
    }

    public void setType(TileType newType) {
        System.out.println(newType + " must replace " + type);
        type = newType;
    }

    public boolean hasEntity() {
        return entity != null;
    }

    public boolean hasItems() {
        return !items.isEmpty();
    }

    public boolean isWalkable() {
        return type != TileType.WALL;
    }

    public void onMove() {
        if (type == TileType.DOOR) {
            type = TileType.FLOOR;
        }
    }

    public Entity getEntity() {
        return entity;
    }

    public void deleteEntity() {
        entity = null;
    }
}
