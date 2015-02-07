angular.module('volunteersTable', ['angular-table']).controller('volunteerController', ['$scope', '$window', '$filter', function($scope, $window, $filter){

  $scope.volunteers = {};

  /** redo this **/
  function load() {
    setTimeout(function(){
      $scope.volunteers = $window.valghalla_volunteers;
      $scope.$apply();
    }, 500);
  }
  load();

  $scope.config = {
    itemsPerPage: 15,
    fillLastPage: true
  };

  $scope.reset = function() {
    $scope.query = '';
    load();
  };

  $scope.updateFilteredList = function() {
    $scope.volunteers = $filter("filter")($window.valghalla_volunteers, $scope.query);
  };
}]);
