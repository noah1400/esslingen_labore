package swa.filer.payload.request;

import jakarta.validation.constraints.NotBlank;

public class UpdateUserRequest {
    
    @NotBlank
    private String email;

    @NotBlank
    private String firstName;

    @NotBlank
    private String lastName;

    @NotBlank
    private String role;

    @NotBlank
    private String dateOfBirth;

    public String getEmail() {
        return this.email;
    }

    public void setEmail(String _email) {
        this.email = _email;
    }

    public String getFirstName() {
        return this.firstName;
    }

    public void setFirstName(String _firstName) {
        this.firstName = _firstName;
    }

    public String getLastName() {
        return this.lastName;
    }

    public void setLastName(String _lastName) {
        this.lastName = _lastName;
    }

    public String getRole() {
        return this.role;
    }

    public void setRole(String _role) {
        this.role = _role;
    }

    public String getDateOfBirth() {
        return this.dateOfBirth;
    }

    public void setDateOfBirth(String _dob) {
        this.dateOfBirth = _dob;
    }

}
