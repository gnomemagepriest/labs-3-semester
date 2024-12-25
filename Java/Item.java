package Java;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Item implements Cloneable {
    protected String name;
    protected char symbol;
    protected List<String> tags;

    public Item(String name) {
        this.name = name;
        this.symbol = name.charAt(0);
        this.tags = new ArrayList<>();
    }

    public Item() {
        this.name = "";
        this.symbol = '\0';
        this.tags = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public char getSymbol() {
        return symbol;
    }

    public void addTag(String tag) {
        tags.add(tag);
    }

     // Мелкое клонирование
    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    // Глубокое клонирование
    public Item deepClone() throws CloneNotSupportedException {
        Item cloned = (Item) super.clone();
        cloned.tags = new ArrayList<>(this.tags);
        return cloned;
    }

    @Override
    public String toString() {
        return "Item name: " + this.name + " " + tags.toString();
    }
}
