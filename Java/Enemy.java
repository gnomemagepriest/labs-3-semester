package Java;

public class Enemy extends Entity {
    private int xpValue;

    public Enemy() {
        super("Zombie", 10, 1, 7, 1, 'Z'); // Инициализация через конструктор родительского класса
        this.xpValue = 50;
    }

    public Enemy(int health, int attack, int defense, 
                int level, int xpValue, 
                String name, char symbol) {
        super(name, health, defense, attack, level, symbol);
        this.xpValue = xpValue;
    }

    @Override
    protected void onLevelUp() {
        this.health += 5; 
        this.defense += 1;
        this.xpValue += 50;
    }

    public int getLevel() {
        return level;
    }

    public int getXPValue() {
        return xpValue;
    }

    @Override
    public String toString() {
        return super.toString() + 
               "XP value: " + xpValue + "\n";
    }
}
