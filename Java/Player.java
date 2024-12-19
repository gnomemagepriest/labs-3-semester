package Java;

public class Player extends Entity {
    private int xp;
    private char input;

    public Player() {
        health = 50;
        defense = 5;
        level = 1;
        xp = 0;
        name = "Player";
        symbol = '@';
        x = 10;
        y = 10;
    }

    public boolean isAlive() {
        return health > 0;
    }

    public void setInput(char newInput) {
        input = newInput;
    }
}
