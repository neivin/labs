import java.sql.*;

class MySQL{

  //Credentials
  static final String USER = "mathewn";
  static final String PASS = "A42750mathewn";

  //JDBC driver name and database URL
  static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
  static final String DB_URL = "jdbc:mysql://eon.socs.uoguelph.ca/" + USER;


  public static void main(String[] args){

    Connection conn = null;
    Statement stmt = null;

    try{
        // Register JDBC driver
        Class.forName(JDBC_DRIVER);

        //Connect to database
        conn = DriverManager.getConnection(DB_URL, USER, PASS);

        // Create statement for selected connection/db
        stmt = conn.createStatement();

        // Use if exists for assignment
        stmt.executeUpdate("CREATE TABLE Employees (id INTEGER, first VARCHAR(45), last VARCHAR(45), age INTEGER)");

        stmt.executeUpdate("INSERT INTO Employees VALUES (1, 'Jack', 'Dorsey', 49)");

        String sqlq;
        sqlq = "SELECT id, first, last, age FROM Employees";

        ResultSet rs = stmt.executeQuery(sqlq);

        // while rs is iterating
        while(rs.next()){
            int id = rs.getInt("id");
            int age = rs.getInt("age");

            String first = rs.getString("first");
            String last = rs.getString("last");

            System.out.println(id + " " +first + " " +last + " " +age );

        }

        /********** Cleanup *********/
        // Close result set
        rs.close();

        //Close statement
        stmt.close();

        //Close connection
        conn.close();

    }
    catch(Exception e){
      e.printStackTrace();
    }


  } //END OF MAIN

}
