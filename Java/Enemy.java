package Java;

public class Enemy extends Entity {
    private int xpValue;
    private int aggression;

    public Enemy() {
        name = "Zombie";
        health = 5;
        defense = 1;
        level = 1;
        aggression = 100;
        xpValue = 50;
        symbol = 'Z';
    }

    public int getLevel() {
        return level;
    }

    public int getXPValue() {
        return xpValue;
    }
}
