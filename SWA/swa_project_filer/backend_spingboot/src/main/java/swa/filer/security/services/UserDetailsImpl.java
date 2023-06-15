package swa.filer.security.services;

import java.util.Collection;
import java.util.Date;
import java.util.Objects;

import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

import com.fasterxml.jackson.annotation.JsonIgnore;

import swa.filer.models.User;

public class UserDetailsImpl implements UserDetails{

    private static final long serialVersionUID = 1L;

    private Long id;

    private String email;

    @JsonIgnore
    private String password;

    private String firstName;

    private String lastName;

    private Date dob;

    public UserDetailsImpl(Long id, String email, String password, String firstName, String lastName, Date dob) {
        this.id = id;
        this.email = email;
        this.password = password;
        this.firstName = firstName;
        this.lastName = lastName;
        this.dob = dob;
    }

    public static UserDetailsImpl build(User user) {
        return new UserDetailsImpl(
            user.getId(), 
            user.getEmail(), 
            user.getPassword(), 
            user.getFirstName(), 
            user.getLastName(), 
            user.getDateOfBirth());
    }

    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return null;
    }

    @Override
    public String getPassword() {
        return this.password;
    }

    @Override
    public String getUsername() {
        return this.email; // username is the email address
    }

    public String getEmail(){
        return this.email;
    }

    public Long getId(){
        return this.id;
    }

    public String getFirstName(){
        return this.firstName;
    }

    public String getLastName(){
        return this.lastName;
    }

    public Date getDob(){
        return this.dob;
    }

    @Override
    public boolean isAccountNonExpired() {
        return true;
    }

    @Override
    public boolean isAccountNonLocked() {
        return true;
    }

    @Override
    public boolean isCredentialsNonExpired() {
        return true;
    }

    @Override
    public boolean isEnabled() {
        return true;
    }

    @Override
    public boolean equals(Object _obj)
    {
        if (this  == _obj) return true;
        if (_obj == null || getClass() != _obj.getClass()) return false;
        UserDetailsImpl user = (UserDetailsImpl) _obj;
        return Objects.equals(id, user.id);
    }
    
}
