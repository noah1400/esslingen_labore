package swa.filer.controller;

import java.util.List;
import java.util.Optional;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;
import swa.filer.models.Directory;
import swa.filer.models.File;
import swa.filer.models.Group;
import swa.filer.models.User;
import swa.filer.payload.request.DirectoryRequest;
import swa.filer.payload.request.FileRequest;
import swa.filer.payload.response.MessageResponse;

@RestController
public class DirectoryController extends ApiController{


    @GetMapping("/directories")
    public ResponseEntity<List<Directory>> getAllDirectories() {
        List<Directory> users = directoryRepository.findAll();
        return new ResponseEntity<>(users, HttpStatus.OK);
    }

    @GetMapping("/directory/{directory-id}")
    public ResponseEntity<?> getDirectoryInformation(@PathVariable("directory-id") Long directoryId) {
        Optional<Directory> directory = directoryRepository.findById(directoryId);
        if (directory.isPresent()) {
            return ResponseEntity.ok(directory.get());
        } else {
            return ResponseEntity.notFound().build();
        }
    }
    /*
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!NOT TESTED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     */
    @PutMapping("/directory/{directory-id}")
    public ResponseEntity<?> updateDirectory(@PathVariable("directory-id") Long directoryId,
                                        @Valid @RequestBody DirectoryRequest directoryRequest) {


        Optional<Directory> optionalDirectory = directoryRepository.findById(directoryId);
        Optional<Group> group = groupRepository.findById( directoryRequest.getGroup());

        if (optionalDirectory.isEmpty()) {
            return ResponseEntity.status(HttpStatus.NOT_FOUND).body("Directory not found.");
        }
        Directory DirToBeUpdated = optionalDirectory.get();

        DirToBeUpdated.setName(directoryRequest.getDirname());
        DirToBeUpdated.setUser_id(directoryRequest.getUserID());
        DirToBeUpdated.setSubdir_id(directoryRequest.getSubdirID());
        DirToBeUpdated.setGroup_id(group.get());

        directoryRepository.save(DirToBeUpdated);
        return ResponseEntity.ok(new MessageResponse("Directory updated sucessfully! \n directoryname: " + DirToBeUpdated.getName()  ));

    }


    @GetMapping("/user/{user-id}/directory/")
    public ResponseEntity<?> getUserDirectoryInformation(@PathVariable("user-id") Long userID) {
        List<Directory> directory = directoryRepository.findAllByUserId(userID);
        if (!directory.isEmpty()) {
            return ResponseEntity.ok(directory);
        } else {
            return ResponseEntity.notFound().build();
        }
    }
    @GetMapping("/user/{user-id}/directory/{directory-name}/subdir")
    public ResponseEntity<?> getUserSubDirInformation(@PathVariable("user-id") Long userID,
                                                      @PathVariable("directory-name") String dir_name ) {
        List<Directory> directory = (dir_name.equals(new String("null"))) ? directoryRepository.findHomeDirByDirByUserID(userID) : directoryRepository.findSubDirByDirIDAndUserID(userID, dir_name);
        if (!directory.isEmpty()) {
            return ResponseEntity.ok(directory);
        } else {
            return ResponseEntity.notFound().build();
        }

    }
    @GetMapping("/user/{user-id}/directory/{directory-name}/id")
    public ResponseEntity<?> getDirectoryIdByName(@PathVariable("user-id") Long userID,
                                                      @PathVariable("directory-name") String dir_name ) {
        List<Directory> directory = directoryRepository.findDirIDByName(userID, dir_name);
        if (!directory.isEmpty()) {
            return ResponseEntity.ok(directory);
        } else {
            return ResponseEntity.notFound().build();
        }

    }

    @PostMapping("/user/{user-id}/directory/{directory-id}")
    public ResponseEntity<?> createDirectory(
            @PathVariable("user-id") Long userID,
            @PathVariable("directory-id") Long dir_id,
            @Valid @RequestBody DirectoryRequest directoryRequest) {

        Optional<Directory> dir_temp = directoryRepository.findById(dir_id);
        Optional<User> user = userRepository.findById(userID);
        Optional<Group> group = groupRepository.findById( directoryRequest.getGroup());
        if (!dir_temp.isPresent()) {
            return ResponseEntity.notFound().build();
        }
        if (!user.isPresent()) {
            return ResponseEntity.notFound().build();
        }
        if (!user.isPresent()) {
            return ResponseEntity.notFound().build();
        }
        // Create new directory
        Directory dir  = new Directory( group.get(),
                                        user.get(),
                                        directoryRequest.getDirname(),
                                        dir_temp.get());

        directoryRepository.save(dir);
        return ResponseEntity.ok(new MessageResponse("Directory: " + directoryRequest.getDirname() +  " created successfully!"));
    }
    
}
