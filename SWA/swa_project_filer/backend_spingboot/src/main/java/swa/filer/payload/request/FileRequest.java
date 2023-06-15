package swa.filer.payload.request;

import swa.filer.models.Directory;

public class FileRequest {


    private Directory directory_id;

    private String filename;

    private String storepath;

    private Long filesize;

    public Directory getDirectory_id() {
        return directory_id;
    }

    public void setDirectory_id(Directory directory_id) {
        this.directory_id = directory_id;
    }



    public String getFilename() {
        return filename;
    }

    public void setFilename(String filename) {
        this.filename = filename;
    }

    public String getStorepath() {
        return storepath;
    }

    public void setStorepath(String storepath) {
        this.storepath = storepath;
    }

    public Long getFilesize() {
        return filesize;
    }

    public void setFilesize(Long filesize) {
        this.filesize = filesize;
    }
}
