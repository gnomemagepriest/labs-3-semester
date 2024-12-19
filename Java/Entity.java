package Java;

public class Entity
{
    protected String name;
    protected char symbol;
    protected int health, defense, level;
    public int x, y;

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
}