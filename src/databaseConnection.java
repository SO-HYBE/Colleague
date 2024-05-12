
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.*;
import javax.swing.JOptionPane;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author fahim
 */

public class databaseConnection {
    //PreparedStatement pst;
    final static String JDBC_DRIVER="com.mysql.cj.jdbc.Driver";
    final static String url = "jdbc:mysql://localhost:3306/colleague";
    final static String username = "root";
    final static String password = "!Mm181120022002";
     
    databaseConnection()
    {
        
    }
    
    public static Connection connection()
    {
        try
        {
            Class.forName(JDBC_DRIVER);
            Connection con=DriverManager.getConnection(url,username,password);
            return con;
        }
        catch(ClassNotFoundException | SQLException e)
        {
            JOptionPane.showMessageDialog(null, e);
            return null;
        }
    }
}
