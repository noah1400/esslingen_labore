package swa.filer.models;

import jakarta.persistence.*;

@Entity
@Table(name = "tfiles")
public class File {
        @Id
        @GeneratedValue(strategy = GenerationType.IDENTITY)
        private Long file_id;
        @ManyToOne(cascade = CascadeType.ALL)
        @JoinColumn(referencedColumnName = "directory_id")
        private Directory directory_id; // Foreign Key

        @Column(name = "filesize", nullable = true, length = 255)
        private Long filesize;

        @Column(name = "filename", nullable = false, length = 255)
        private String filename;
        @Column(name = "storepath", nullable = true, length = 255)
        private String storepath;


        // constructors

        public File(){
            // empty constructor
        }

        public File(Directory dir_id, Long file_size, String file_name, String store_path) {
            this.directory_id = dir_id;
            this.filesize = file_size;
            this.filename = file_name;
            this.storepath = store_path;
        }

        public Directory getDirID() {
            return this.directory_id;
        }
        public Long getFileID() {
        return this.file_id;
    }
        public void setDirID(Directory dir_id) {
            this.directory_id = dir_id;
        }

        public void setFilesize(Long fs){
            this.filesize = fs;
        }

        public Long getFilesize(){
            return this.filesize;
        }

        public String getStorepath(){
            return this.storepath;
        }

        public void setStorepath(String sp){
            this.storepath = sp;
        }

        public String getFilename(){
            return this.filename;
        }
        public void setFilename(String fn){
            this.filename = fn;
        }



}
