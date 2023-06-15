package swa.filer.controller;

import java.util.List;
import java.util.Optional;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import jakarta.validation.Valid;
import swa.filer.models.Directory;
import swa.filer.models.File;
import swa.filer.models.User;
import swa.filer.payload.request.DirectoryRequest;
import swa.filer.payload.request.FileRequest;
import swa.filer.payload.response.MessageResponse;
import swa.filer.repository.FileRepository;

@RestController
public class FileController extends ApiController{

    @PostMapping("/user/{user-id}/directory/{directory-id}/files")
    public ResponseEntity<?> createFile(
        @PathVariable("user-id") Long userID,
        @PathVariable("directory-id") Long dir_id,
        @Valid @RequestBody FileRequest fileRequest) {

        Optional<Directory> dir = directoryRepository.findById(dir_id);
        if (!dir.isPresent()) {
            return ResponseEntity.notFound().build();
        }

        // Create new file
        File file  = new File(  dir.get(),
                                fileRequest.getFilesize(),
                                fileRequest.getFilename(),
                                fileRequest.getStorepath());

        fileRepository.save(file);
        return ResponseEntity.ok(new MessageResponse("File: " + fileRequest.getFilename() +  " created successfully at : " + fileRequest.getStorepath()));
    }


    @GetMapping("/user/directory/{directory-name}/files")
    public ResponseEntity<?> getFileInformation(@PathVariable("directory-name") String dir_name) {

        List<File> file = fileRepository.findFilesByDirID(dir_name);

        return new ResponseEntity<>(file, HttpStatus.OK);

    }

    @PutMapping("/user/{user-id}/directory/{directory-id}/files")
    public ResponseEntity<?> updateFile(@PathVariable("user-id") Long userId,
                                        @PathVariable("directory-id") Long directoryId,
                                        @Valid @RequestBody FileRequest fileRequest) {


        File FileToBeUpdated = fileRepository.findFileByUserIDAndDirID(userId, directoryId);

        FileToBeUpdated.setFilename(fileRequest.getFilename());
        FileToBeUpdated.setFilesize(fileRequest.getFilesize());
        FileToBeUpdated.setStorepath(fileRequest.getStorepath());

        fileRepository.save(FileToBeUpdated);
        return ResponseEntity.ok(new MessageResponse("File updated sucessfully! \n filename: " + FileToBeUpdated.getFilename() + "\n filesize: " + FileToBeUpdated.getFilesize() + "\n storepath: " + FileToBeUpdated.getStorepath()));

    }

    @DeleteMapping("/user/directory/files/{file-id}")
    public ResponseEntity<?> deleteFile(@PathVariable("file-id") Long fileId) {

        File fileToBeDeleted = fileRepository.findFileById(fileId);

        if (fileToBeDeleted == null) {
            // File not found, return an appropriate response
            return ResponseEntity.status(HttpStatus.NOT_FOUND).body("File not found.");
        }

        fileRepository.delete(fileToBeDeleted);

        return ResponseEntity.ok("File deleted successfully.");
    }






}
