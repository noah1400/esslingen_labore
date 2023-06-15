package swa.filer.models;

import jakarta.persistence.*;
import org.hibernate.annotations.CreationTimestamp;
import org.hibernate.annotations.UpdateTimestamp;

import java.time.LocalDateTime;
import java.util.List;

@Entity
@Table(name = "tgroups")
public class Group {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long group_id;
    private String name;
    @ManyToOne(cascade = CascadeType.DETACH)
    @JoinColumn(referencedColumnName = "id")
    private User founder_id; // Foreign Key
    @CreationTimestamp
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "created_at", nullable = false)
    private LocalDateTime created_at;
    @UpdateTimestamp
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "updated_at", nullable = false)
    private LocalDateTime updated_at;

    public Group(){}
    public Group(User founder_id, String name){
        this.founder_id = founder_id;
        this.name = name;
    }

    public Long getId(){
        return this.group_id;
    }
    public User getFounder_id(){
        return founder_id;
    }
    public void setFounder_id(User _founder_id){
        this.founder_id = _founder_id;
    }
    public LocalDateTime getCreated_at(){
        return this.created_at;
    }
    public LocalDateTime getUpdated_at(){
        return this.updated_at;
    }
    public String getName(){
        return this.name;
    }
    public void setName(String _name){
        this.name = _name;
    }
}
