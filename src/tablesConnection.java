
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.table.DefaultTableModel;


/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author fahim
 */
public class tablesConnection {
    
    
    public static void students()
    {
            try {
            Statement st = databaseConnection.connection().createStatement();
            //mySQL Query
            String sql="select * from students";
            ResultSet rs=st.executeQuery(sql);
            while(rs.next()) // data will be added until finished
            {
                String name=String.valueOf(rs.getString("Name"));
                String id=String.valueOf(rs.getString("ID"));
                double GPA=rs.getDouble("GPA");
                String level=String.valueOf(rs.getString("Level"));
                // array for storing table data
                String studentsData[]={name,id,String.valueOf(GPA),level};
                DefaultTableModel tblModel=(DefaultTableModel)StudentManager.getStudentsTable().getModel();
                // add array data into students table
                tblModel.addRow(studentsData);
            }
        } catch (SQLException ex) {
            Logger.getLogger(StudentManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public static void staff()
    {
            try {
            Statement st = databaseConnection.connection().createStatement();
            //mySQL Query
            String sql="select * from staff";
            ResultSet rs=st.executeQuery(sql);
            while(rs.next()) // data will be added until finished
            {
                String name=String.valueOf(rs.getString("Name"));
                String id=String.valueOf(rs.getString("ID"));
                String phone=String.valueOf(rs.getString("phone"));
                // array for storing table data
                String staffData[]={name,id,phone};
                DefaultTableModel tblModel=(DefaultTableModel)StudentManager.getStaffTable().getModel();
                // add array data into table
                tblModel.addRow(staffData);
            }
        } catch (SQLException ex) {
            Logger.getLogger(StudentManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public static void courses()
    {
            try {
            Statement st = databaseConnection.connection().createStatement();
            //mySQL Query
            String sql="select * from courses";
            ResultSet rs=st.executeQuery(sql);
            while(rs.next()) // data will be added until finished
            {
                String name=String.valueOf(rs.getString("Name"));
                String hours=String.valueOf(rs.getString("hours"));
                String enrolled=String.valueOf(rs.getString("enrolled"));
                // array for storing table data
                String coursesData[]={name,hours,enrolled};
                DefaultTableModel tblModel=(DefaultTableModel)StudentManager.getCoursesTable().getModel();
                // add array data into table
                tblModel.addRow(coursesData);
            }
        } catch (SQLException ex) {
            Logger.getLogger(StudentManager.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
