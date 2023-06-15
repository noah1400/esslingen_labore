package swa.filer.models;

import jakarta.persistence.*;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import com.fasterxml.jackson.annotation.JsonIgnore;

@Entity
@Table(name = "tusers")
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false, unique = true, length = 45)
    private String email;

    @Column(nullable = false, length = 64)
    private String password;

    @Column(name = "fName", nullable = false, length = 20)
    private String firstName;

    @Column(name = "lName", nullable = false, length = 20)
    private String lastName;

    @Column(name = "role", nullable = false, length = 20)
    private String role;

    @Column(name = "dob", nullable = false)
    @Temporal(TemporalType.DATE)
    private Date dateOfBirth;


    // constructors

    public User(){
        // empty constructor
    }

    public User(String _email, String _password, String _firstName, String _lastName, String _role, Date _dob){
        this.email = _email;
        this.password = _password;
        this.firstName = _firstName;
        this.lastName = _lastName;
        this.role = _role;
        this.dateOfBirth = _dob;
    }

    public User(String _email, String _password, String _firstName, String _lastName, String _role, String _dob){
        this.email = _email;
        this.password = _password;
        this.firstName = _firstName;
        this.lastName = _lastName;
        this.role = _role;
        // this.dateOfBirth = _dob;
        SimpleDateFormat formatter = new SimpleDateFormat("dd.MM.yyyy");
        try{
            this.dateOfBirth = formatter.parse(_dob);
        }catch(Exception e){
            System.out.println("Error parsing date: " + e.getMessage());
        }
    }

    // getters and setters
    public Long getId(){
        return this.id;
    }
    public String getEmail(){
        return this.email;
    }
    public void setEmail(String _email){
        this.email = _email;
    }

    @JsonIgnore
    public String getPassword(){
        return this.password;
    }

    public void setPassword(String _password){
        this.password = _password;
    }

    public String getFirstName(){
        return this.firstName;
    }

    public void setFirstName(String _firstName){
        this.firstName = _firstName;
    }

    public String getLastName(){
        return this.lastName;
    }

    public void setLastName(String _lastName){
        this.lastName = _lastName;
    }

    public String getRole(){
        return this.role;
    }

    public void setRole(String _role){
        this.role = _role;
    }

    public Date getDateOfBirth(){
        return this.dateOfBirth;
    }

    public void setDateOfBirth(Date _dob){
        this.dateOfBirth = _dob;
    }

}