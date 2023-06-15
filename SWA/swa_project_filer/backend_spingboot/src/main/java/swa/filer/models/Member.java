package swa.filer.models;

import jakarta.annotation.Generated;
import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;

@Entity
@Table(name = "tgroupmembers")
public class Member {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(cascade = CascadeType.DETACH)
    @JoinColumn(referencedColumnName = "id")
    private User user; // Foreign Key

    @ManyToOne(cascade = CascadeType.DETACH)
    @JoinColumn(referencedColumnName = "group_id")
    private Group group; // Foreign Key
    

    // constructors
    public Member(){
        // empty constructor
    }

    public Member(User _user, Group _group){
        this.user = _user;
        this.group = _group;
    }
}
