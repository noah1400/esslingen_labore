package swa.filer.payload.request;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;

public class SignupRequest {
    
    // Email
    @NotBlank
    @Size (max = 50)
    private String email;

    @NotBlank
    @Size (max = 20)
    private String firstName;

    @NotBlank
    @Size (max = 20)
    private String lastName;

    @NotBlank
    @Size (max = 20)
    private String role;

    @NotBlank
    @Size (max = 20)
    private String dateOfBirth;

    @NotBlank
    @Size (min  = 6, max = 40)
    private String password;

    public String getEmail(){
        return this.email;
    }

    public void setEmail(String _email){
        this.email = _email;
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

    public String getDateOfBirth(){
        return this.dateOfBirth;
    }

    public void setDateOfBirth(String _dob){
        this.dateOfBirth = _dob;
    }

    public String getPassword(){
        return this.password;
    }

    public void setPassword(String _password){
        this.password = _password;
    }
}
