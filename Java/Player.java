package Java;

import java.util.ArrayList;

public class Player extends Entity implements Killable {
    private int xp;
    private char input;

    public Player() {
        super("Player", 50, 5, 5, 1, '@');
        this.xp = 0;
        this.x = 10;
        this.y = 10;
    }

    @Override
    public int getHealth() {
        return health;
    }

    @Override
    public boolean isAlive() {
        return health > 0;
    }

    public void setInput(char newInput) {
        input = newInput;
    }

    @Override
    protected void onLevelUp() {
        this.defense += 1;
        this.attack += 1;
        this.health += 10;
    }

    public void gainXP(int amount) {
        xp += amount;
        if (xp >= level * 100) {
            level += 1;
            onLevelUp();
        }
    }

    @Override
    public String toString() {
        return "Player XP: " + xp + "\n" +
               "Player level: " + level + "\n";
    }
}
