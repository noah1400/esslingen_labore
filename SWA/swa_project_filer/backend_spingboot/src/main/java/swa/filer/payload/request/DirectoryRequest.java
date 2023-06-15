package swa.filer.payload.request;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;
import swa.filer.models.Directory;
import swa.filer.models.Group;
import swa.filer.models.User;

public class DirectoryRequest {

    private Long group_id;

    @NotBlank
    @Size (max = 50)
    private String dirname;


    private User user_id;

    private Directory subdir_id;


    public Long getGroup() {
        return this.group_id;
    }

    public void setGroup_id(Long group_id) {
        this.group_id = group_id;
    }

    public String getDirname(){
        return this.dirname;
    }

    public void setDirname(String dirname) {
        this.dirname = dirname;
    }

    public User getUserID() {
        return this.user_id;
    }

    public void setUserID(User user_id) {
        this.user_id = user_id;
    }

    public Directory getSubdirID(){
        return this.subdir_id;
    }

    public void setSubdirID(Directory subdir_id){
        this.subdir_id = subdir_id;
    }





}
