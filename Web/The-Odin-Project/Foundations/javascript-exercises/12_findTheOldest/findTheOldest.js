const findTheOldest = function (people) {
    return people.reduce((accumulator, person) => {
        return getAge(accumulator) > getAge(person) ? accumulator : person;
    });

    function getAge(person) {
        return (person.yearOfDeath ? person.yearOfDeath : (new Date()).getFullYear()) - person.yearOfBirth;
    }
};

// Do not edit below this line
module.exports = findTheOldest;
