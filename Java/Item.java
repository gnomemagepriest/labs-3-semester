package Java;

public class Item {
    protected String name;
    protected char symbol;

    public Item(String name) {
        this.name = name;
        this.symbol = name.charAt(0);
    }

    public String getName() {
        return name;
    }

    public char getSymbol() {
        return symbol;
    }
}
