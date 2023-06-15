package swa.filer;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase.Replace;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.test.annotation.Rollback;

import swa.filer.models.User;
import swa.filer.repository.UserRepository;

//import java.util.Date;
import java.sql.Date;

import static org.assertj.core.api.Assertions.assertThat;



@DataJpaTest
@AutoConfigureTestDatabase(replace = Replace.NONE)
@Rollback(false)
public class UserRepositoryTests {

    @Autowired
    private TestEntityManager entityManager;

    @Autowired
    private UserRepository repo;

    // test methods go below

    @Test
    public void testCreateUser() {
        User user = new User();
        user.setEmail("astridbeck@gmail.com");
        user.setPassword("ginlife");
        user.setFirstName("Astrid");
        user.setLastName("Beck");
        user.setDateOfBirth(Date.valueOf("1960-05-30"));

        User savedUser = repo.save(user);

        User existUser = entityManager.find(User.class, savedUser.getId());

        assertThat(user.getEmail()).isEqualTo(existUser.getEmail());

    }
}