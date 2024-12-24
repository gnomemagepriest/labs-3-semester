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

    protected Entity takeDamage(int damageTaken) {
        health -= DamageCalculator.calculateDamage(damageTaken, defense);
        return this;
    }

    public char getChar() {
        return symbol;
    }

    public int getHealth() {
        return health;
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

class DamageCalculator {
    public static int calculateDamage(int baseDamage, int defense) {
        int damage = baseDamage - defense;
        return Math.max(damage, 0); // Урон не может быть отрицательным
    }
}