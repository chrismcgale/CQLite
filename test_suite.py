import subprocess
import pytest

class TestDatabase:
    def run_script(self, commands):
        """
        Runs a series of commands against the database CLI and returns the output.
        
        Args:
            commands (list): List of command strings to execute
            
        Returns:
            list: Output lines from the database
        """
        # Start the database process
        process = subprocess.Popen(
            ['./db'],  # Replace with your database executable path
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True  # This ensures text mode (vs binary)
        )
        
        # Join commands with newlines to create input
        input_commands = '\n'.join(commands) + '\n'
        
        # Send commands and get output
        stdout, stderr = process.communicate(input_commands)
        
        # Split output into lines and remove empty lines
        return [line for line in stdout.split('\n') if line]

    def test_insert_and_retrieve_row(self):
        """Tests basic insert and select functionality"""
        result = self.run_script([
            "insert 1 user1 person1@example.com",
            "select",
            ".exit"
        ])
        
        assert result == [
            "db > Executed.",
            "db > (1, user1, person1@example.com)",
            "Executed.",
            "db > "
        ]

    def test_table_empty_at_start(self):
        """Tests that table is empty when database starts"""
        result = self.run_script([
            "select",
            ".exit"
        ])
        
        assert result == [
            "db > Executed.",
            "db > "
        ]

    def test_insert_error_on_duplicate_id(self):
        """Tests error handling when inserting duplicate IDs"""
        result = self.run_script([
            "insert 1 user1 person1@example.com",
            "insert 1 user2 person2@example.com",  # Same ID as above
            ".exit"
        ])
        
        assert result == [
            "db > Executed.",
            "db > Error: Duplicate ID.",
            "db > "
        ]


    def test_invalid_command(self):
        """Tests handling of invalid commands"""
        result = self.run_script([
            "invalid_command",
            ".exit"
        ])
        
        assert result == [
            "db > Unrecognized command: invalid_command",
            "db > "
        ]
        
    def test_long_string(self):
        """Tests handling max length strings"""
        long_user = "a" * 32
        long_email = "a" * 255
        result = self.run_script([
            f"insert 1 {long_user} {long_email}",
            "select",
            ".exit"
        ])
        
        assert result == [
             "db > Executed.",
            f"db > (1, {long_user}, {long_email})",
            "db > Executed.",
            "db > "
        ]
        
    def test_too_long_string(self):
        """Tests handling of too long strings"""
        long_email = "a" * 256
        result = self.run_script([
            f"insert 1 user1 {long_email}",
            "select",
            ".exit"
        ])
        
        assert result == [
            "db > String is too long.",
            "db > Executed.",
            "db > "
        ]
        
    def test_negitive_id(self):
        """Tests handling of negative id"""
        result = self.run_script([
            "insert -1 user1 person1@example.com",
            ".exit"
        ])
        
        assert result == [
            "db > ID must be positive.",
            "db > "
        ]

if __name__ == '__main__':
    pytest.main([__file__])