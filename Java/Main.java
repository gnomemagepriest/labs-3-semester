package Java;

public class Main
{
  public static void main(String[] args) {
    try {
      Game game = new Game();
      
      game.run();
    }
    catch (RuntimeException e) {
      System.out.println("Игра не может быть создана. Ошибка: " + e);
    }
  }
}
