package Java;

public class Weapon extends Item {
    private int damage;
    private int enhancement;

    public Weapon() {
        super();
        this.damage = 0;
        this.enhancement = 0;
    }

    public Weapon(String name, int damage) {
        super(name);
        this.damage = damage;
        this.enhancement = 0;
    }

    public Weapon(String name, int damage, int enhancement) {
        super(name);
        this.damage = damage;
        this.enhancement = enhancement;
    }

    public int getDamage() {
        return damage;
    }

    @Override
    public String getName() {
        return super.getName() + " +" + enhancement;
    }
}
