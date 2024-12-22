package Java;

import java.util.ArrayList;

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
        inventory = new ArrayList<>();
    }

    public boolean isAlive() {
        return health > 0;
    }

    public void setInput(char newInput) {
        input = newInput;
    }

    public String getInventoryDescription() {
        if (inventory.isEmpty()) {
            return "You don't have any items.";
        }

        StringBuilder result = new StringBuilder("You have:\n");
        for (Item item : inventory) {
            result.append("- ").append(item.getName()).append("\n");
        }
        return result.toString();
    }
}
