package Java;

import java.util.ArrayList;
import java.util.List;

public abstract class Entity {
    protected String name;
    protected char symbol;
    protected int health, defense, attack, level;
    protected int x, y;
    public Inventory<Item> inventory;
    private static int totalEntities = 0;

    public Entity() {
        totalEntities++;
        inventory = new Inventory<Item>();
    }

    public Entity(String name, int health, int defense, int attack, int level, char symbol) {
        this.name = name;
        this.health = health;
        this.defense = defense;
        this.attack = attack;
        this.level = level;
        this.symbol = symbol;
        totalEntities++;
        inventory = new Inventory<Item>();
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

    public int[] getPosition() {
        return new int[]{x, y};
    }

    public void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

    @Override
    public String toString() {
        return "Name: " + name + "\n" +
               "Health: " + health + "\n" +
               "Defense: " + defense + "\n" +
               "Level: " + level + "\n" +
               "Position: (" + x + ", " + y + ")\n" +
               "Symbol: " + symbol + "\n";
    }

    protected abstract void onLevelUp();
}

class DamageCalculator {
    public static int calculateDamage(int baseDamage, int defense) {
        int damage = baseDamage - defense;
        return Math.max(damage, 0); // Урон не может быть отрицательным
    }
}