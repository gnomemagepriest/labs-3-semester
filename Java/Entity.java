package Java;

import java.util.List;

public class Entity
{
    protected String name;
    protected char symbol;
    protected int health, defense, level;
    protected int x, y;
    protected List<Item> inventory;
    private static int totalEntities = 0;

    public Entity() {
        totalEntities++;
    }

    public static int getTotalEntities() {
        return totalEntities;
    }

    protected boolean takeDamage(int damageTaken) {
        damageTaken -= defense;
        if (damageTaken > 0) {
            health -= damageTaken;
            return true;
        }
        return false;
    }

    public char getChar() {
        return symbol;
    }

    public String getName() {
        return name;
    }

    public void addItem(Item item) {
        inventory.add(item);
    }

    public int[] getPosition() {
        return new int[]{x, y};
    }

    public void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }
}