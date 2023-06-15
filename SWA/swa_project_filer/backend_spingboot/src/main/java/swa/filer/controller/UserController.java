package swa.filer.controller;

import java.util.List;
import java.util.Optional;

import javax.swing.text.html.Option;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import jakarta.validation.Valid;
import swa.filer.models.Group;
import swa.filer.models.Member;
import swa.filer.models.RefreshToken;
import swa.filer.models.User;
import swa.filer.payload.request.UpdateUserRequest;

@RestController
public class UserController extends ApiController{


    @GetMapping("/users")
    public ResponseEntity<List<User>> getAllUsers() {
        List<User> users = userRepository.findAll();
        return new ResponseEntity<>(users, HttpStatus.OK);
    }

    @GetMapping("/user/{user-id}")
    public ResponseEntity<User> getUserById(@PathVariable("user-id") String userId) {
        Optional<User> userData = userRepository.findById(Long.parseLong(userId));
        if (userData.isPresent()) {
            return new ResponseEntity<>(userData.get(), HttpStatus.OK);
        } else {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @PutMapping("/user/{user-id}/update")
    public ResponseEntity<User> updateUserById(@PathVariable("user-id") String userId, @Valid @RequestBody UpdateUserRequest updateUserRequest) {
        Optional<User> userData = userRepository.findById(Long.parseLong(userId));
        if (userData.isPresent())
        {
            User user = userData.get();
            user.setFirstName(updateUserRequest.getFirstName());
            user.setLastName(updateUserRequest.getLastName());
            user.setEmail(updateUserRequest.getEmail());
            user.setRole(updateUserRequest.getRole());
            userRepository.save(user);

            return ResponseEntity.ok(user);
        } 
        return ResponseEntity.notFound().build();
    }
    
}
