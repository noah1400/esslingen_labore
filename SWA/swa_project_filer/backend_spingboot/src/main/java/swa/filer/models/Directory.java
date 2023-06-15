package swa.filer.models;

import jakarta.persistence.*;
import org.hibernate.annotations.CreationTimestamp;
import org.hibernate.annotations.UpdateTimestamp;

import java.time.LocalDateTime;

@Entity
@Table(name = "tdirectory")
public class Directory {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long directory_id;
    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(referencedColumnName = "group_id")
    private Group group_id; // Foreign Key
    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(referencedColumnName = "id")
    private User user_id; // Foreign Key
    @Column(name = "name", nullable = false, length = 255)
    private String name;
    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(referencedColumnName = "directory_id", nullable = true)
    private Directory subdir_id;
    @CreationTimestamp
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "created_at", nullable = false)
    private LocalDateTime created_at;
    @UpdateTimestamp
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "updated_at", nullable = false)
    private LocalDateTime updated_at;
    // constructors

    public Directory(){
        // empty constructor
    }

    public Directory(Group _group_id, User _user_id, String _name, Directory _subdir_id) {
        this.group_id = _group_id;
        this.user_id = _user_id;
        this.name = _name;
        this.subdir_id = _subdir_id;
    }
    public void setName(String _name) {
        this.name = _name;
    }
    public String getName() {
        return this.name;
    }

    public Long getDirID() {
        return directory_id;
    }
    public Group getGroup_id() {
        return group_id;
    }
    public void setGroup_id(Group _group_id) {
        this.group_id = _group_id;
    }
    public Directory getSubdir_id() {
        return subdir_id;
    }
    public void setSubdir_id(Directory _subdir_id) {
        this.subdir_id = _subdir_id;
    }
    public User getUser_id() {
        return this.user_id;
    }
    public void setUser_id(User _user_id) {
        this.user_id = _user_id;
    }
    public LocalDateTime getCreated_at(){
        return this.created_at;
    }
    public LocalDateTime getUpdated_at(){
        return this.updated_at;
    }
}